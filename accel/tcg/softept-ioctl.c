#include "sysemu/softept.h"

static struct SofteptState softept_state;

static void softept_entry_list_init(void)
{
    struct SofteptEntryVector * vec = &softept_state.softept_entry_vector;

    vec->gpa_list = (hwaddr *)g_malloc0_n(16, sizeof(hwaddr));
    vec->capacity = 16;
    vec->size = 0;
}

void softept_entry_list_insert(hwaddr elem)
{
    struct SofteptEntryVector * vec = &softept_state.softept_entry_vector;

    if(vec->size == vec->capacity){
        int new_capacity = vec->capacity * 2;
        hwaddr * tmp = (hwaddr *)g_malloc0_n(new_capacity, sizeof(hwaddr));

        memcpy(tmp, vec->gpa_list, vec->size * sizeof(hwaddr));
        g_free(vec->gpa_list);
        vec->gpa_list = tmp;

        vec->gpa_list[vec->size++] = elem;
        vec->capacity = new_capacity;
        return;
    }
    vec->gpa_list[vec->size++] = elem;
}

int softept_entry_flush_all(void)
{	
    struct SofteptEntry softepts_entry;
    struct SofteptEntryVector * vec = &softept_state.softept_entry_vector;
    int r = -1;	

    softepts_entry.flush_entry.list = vec->gpa_list;
    softepts_entry.flush_entry.size = vec->size;

    r = softept_ioctl(SOFTEPT_FLUSH_ENTRY, &softepts_entry);

    if(r)
	goto out;
    r = 0;

    out:
        g_free(vec->gpa_list);
        softept_entry_list_init();
        return r;
}

int softept_ioctl(int type, ...)
{
    struct SofteptState *s = &softept_state;
    int ret;
    void *arg;
    va_list ap;

    va_start(ap, type);
    arg = va_arg(ap, void *);
    va_end(ap);

    ret = ioctl(s->fd, type, arg);
    if (ret == -1) {
        ret = -errno;
    }
    return ret;
}

int softept_init(void)
{
    int ret;
    struct SofteptState *s = &softept_state;
    s->pid = getpid();
    s->fd = qemu_open("/dev/softept", O_RDWR);
    if (s->fd == -1) {
        fprintf(stderr, "Could not access espt kernel module: %m\n");
        ret = -errno;
        goto err;
    }

    if(softept_ioctl(SOFTEPT_INIT, &s->pid)){
        ret = -errno;
        goto err;
    }
    return 0;

    err:
        assert(ret < 0);
        if (s->fd != -1) {
	    close(s->fd);
        }
	
    return ret;
}
