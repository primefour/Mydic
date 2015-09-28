package com.Dict.DictApp2;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

public class DictQueryService extends Service {
    public DictQueryService() {

    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }
}
