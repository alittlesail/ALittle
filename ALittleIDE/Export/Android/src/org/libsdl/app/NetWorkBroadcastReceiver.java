package org.libsdl.app;

import android.content.BroadcastReceiver;
import android.content.*;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;

public class NetWorkBroadcastReceiver extends BroadcastReceiver {

    public static NetWorkBroadcastReceiver listener = null;

    public static void Setup()
    {
        listener = new NetWorkBroadcastReceiver();

        IntentFilter filter = new IntentFilter(ConnectivityManager.CONNECTIVITY_ACTION);
        SDLActivity.getContext().registerReceiver(listener, filter);
    }

    public static void Shutdown()
    {
        if (listener == null) return;
        SDLActivity.getContext().unregisterReceiver(listener);
        listener = null;
    }

	public NetWorkBroadcastReceiver() {
        super();
    }

	@Override
	public void onReceive(Context context, Intent intent) {			
		String connectState = "";
        ConnectivityManager cm = (ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE); 
        NetworkInfo activeNetworkInfo = cm.getActiveNetworkInfo();
        if (activeNetworkInfo == null || !activeNetworkInfo.isAvailable())
        {
        	connectState = "OtherSystem_NotifyNetwork_none";
        }
        else
        {
        	int networkType = activeNetworkInfo.getType();
	        if (networkType == ConnectivityManager.TYPE_WIFI)
	        	connectState = "OtherSystem_NotifyNetwork_wifi";
	        else
            	connectState = "OtherSystem_NotifyNetwork_line";
        }
        
    	GlobalFunc.Invoke("__LUAAPI_NetworkChanged", connectState);
	}
}
