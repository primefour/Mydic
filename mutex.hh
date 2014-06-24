/* This file is (c) 2008-2011 Konstantin Isakov <ikm@users.berlios.de>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#ifndef __MUTEX_HH_INCLUDED__
#define __MUTEX_HH_INCLUDED__
#include<pthread.h>

class Mutex
{

    public:
        Mutex();
        ~Mutex();

        /// Locks the given mutex on construction and unlocks on destruction
        class Lock
        {
            Mutex & m;

            public:

            Lock( Mutex & );
            ~Lock();

            private:
            Lock( Lock const & );
        };
    private:
        pthread_mutex_t mMutex;
};

#endif
