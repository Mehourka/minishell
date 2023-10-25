
#include "minishell.h"

//memory block
typedef struct s_mblock
{
    void *address;
    struct s_mblock *next_mb;
}   t_mblock;

//access head of garbage collector everywhere in the program
t_mblock *garbage_collector(void)
{
    static t_mblock head = { NULL, NULL };
    return &head;
}


//malloc stuff and append to the garbage collector
void * gc_calloc(size_t nmemb, size_t size)
{
    t_mblock *new_mb;

    new_mb = ft_calloc(1,sizeof(t_mblock));
    if(!new_mb)
        return NULL;

    new_mb->next_mb = garbage_collector()->next_mb;
    garbage_collector()->next_mb = new_mb;

    new_mb->address = ft_calloc(nmemb,size);
    if(!new_mb->address)
        return NULL;
     
    return new_mb->address;
}


// free specific memory block and its content and connect back the list
void gc_free(void*address)
{
    t_mblock*gc_ptr;
    t_mblock*ptr_copy;

    gc_ptr = garbage_collector()->next_mb;
    ptr_copy = garbage_collector();

    while(gc_ptr)
    {
        if(gc_ptr->address == address)
        {
            ptr_copy->next_mb = gc_ptr->next_mb;
            if(gc_ptr->address)
                free(gc_ptr->address);
            free(gc_ptr);

            return ;
        }
        ptr_copy = gc_ptr;
        gc_ptr = gc_ptr->next_mb;
    }
}

//free entire garbage collector
void gc_free_all(void)
{
    t_mblock*gc_ptr;
    t_mblock*ptr_copy;

    gc_ptr = garbage_collector()->next_mb;
    while(gc_ptr)
    {
        if(gc_ptr->address)
            free(gc_ptr->address);
        ptr_copy = gc_ptr;
        gc_ptr = gc_ptr->next_mb;
        free(ptr_copy);
    }
    garbage_collector()->next_mb = NULL;
}
