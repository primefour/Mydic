/* This file is (c) 2008-2011 Konstantin Isakov <ikm@users.berlios.de>
 * Part of GoldenDict. Licensed under GPLv3 or later, see the LICENSE file */

#include "mutex.hh"

Mutex::Lock::Lock( Mutex & mut):m(mut) {
    pthread_mutex_lock(&(m.mMutex));
}

Mutex::Lock::~Lock() {
    pthread_mutex_unlock(&(m.mMutex));
}

Mutex::Mutex(){
    pthread_mutex_init(&mMutex,NULL);
}

Mutex::~Mutex(){
    pthread_mutex_destroy(&mMutex);
}
