/*
 * All the contents of this file are overwritten during automated
 * testing. Please consider this before changing anything in this file.
 */

#include <types.h>
#include <lib.h>
#include <clock.h>
#include <thread.h>
#include <synch.h>
#include <test.h>
#include <kern/test161.h>
#include <spinlock.h>

/*
 * Use these stubs to test your reader-writer locks.
 */

int rwtest(int nargs, char **args) {
	(void)nargs;
	(void)args;

	int READER_LOCKS = 5;
	struct rwlock *rwlock = rwlock_create("testrwlock");
	for (int i = 0; i != READER_LOCKS; ++i) {
		rwlock_acquire_read(rwlock);
	}
	secprintf(SECRET, "Should panic...", "rwt1");
	rwlock_acquire_write(rwlock);

	/* Should not get here on success. */

	success(TEST161_FAIL, SECRET, "rwt1");

	/* Don't do anything that could panic. */

	return 0;
}

int rwtest2(int nargs, char **args) {
	(void)nargs;
	(void)args;

	struct rwlock *rwlock = rwlock_create("testrwlock");

	secprintf(SECRET, "Should panic...", "rwt2");
	rwlock_release_read(rwlock);

	/* Should not get here on success. */

	success(TEST161_FAIL, SECRET, "rwt2");

	/* Don't do anything that could panic. */

	return 0;
}

int rwtest3(int nargs, char **args) {
	(void)nargs;
	(void)args;

	int READER_LOCKS = 5;
	struct rwlock *rwlock = rwlock_create("testrwlock");
	for (int i = 0; i != READER_LOCKS; ++i) {
		rwlock_acquire_read(rwlock);
	}
	for (int i = 0; i != READER_LOCKS; ++i) {
		rwlock_release_read(rwlock);
	}
	rwlock_acquire_write(rwlock);
	rwlock_release_write(rwlock);

	rwlock_destroy(rwlock);

	kprintf_t("\n");
	success(TEST161_SUCCESS, SECRET, "rwt3");

	return 0;
}

int rwtest4(int nargs, char **args) {
	(void)nargs;
	(void)args;

	struct rwlock *rwlock = rwlock_create("testrwlock");

	secprintf(SECRET, "Should panic...", "rwt1");
	rwlock_release_write(rwlock);

	/* Should not get here on success. */

	success(TEST161_FAIL, SECRET, "rwt4");

	/* Don't do anything that could panic. */
	return 0;
}

int rwtest5(int nargs, char **args) {
	(void)nargs;
	(void)args;

	struct rwlock *rwlock = rwlock_create("testrwlock");
	rwlock_acquire_write(rwlock);

	secprintf(SECRET, "Should panic...", "rwt5");
	rwlock_acquire_read(rwlock);

	/* Should not get here on success. */

	success(TEST161_FAIL, SECRET, "rwt5");

	/* Don't do anything that could panic. */
	return 0;
}
