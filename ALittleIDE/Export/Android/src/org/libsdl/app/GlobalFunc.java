package org.libsdl.app;

import android.content.*;
import android.content.pm.ActivityInfo;
import android.database.Cursor;
import android.location.LocationManager;
import android.media.AudioManager;
import android.net.*;
import android.os.Vibrator;
import android.provider.*;
import android.text.InputType;
import android.text.TextUtils;
import android.telephony.TelephonyManager;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import org.json.*;

import cn.sharesdk.framework.ShareSDK;

public class GlobalFunc {
	public static int screen_width = 0;
	public static int screen_height = 0;
	public static final int file_select = 3;
	public static String wechat_app_id = "";
	// Java invoke
	// C===========================================================================================
	public native static void SurfaceResize();

	public native static void J2CLog(String content);

	public native static void Invoke(String method, String param);

	// C invoke
	// Java===========================================================================================
	public static int C2J_GetScreenWidth() {
		return SDLActivity.mLayout.getWidth();
	}

	public static int C2J_GetScreenHeight() {
		return SDLActivity.mLayout.getHeight();
	}

	public static int C2J_GetStatusBarHeight() {
		// int statusBarHeight = 0;  
		// 获取status_bar_height资源的ID  
		// int resourceId = SDLActivity.getContext().getResources().getIdentifier("status_bar_height", "dimen", "android");  
		// if (resourceId > 0) {  
		    //根据资源ID获取响应的尺寸值  
		//     statusBarHeight = SDLActivity.getContext().getResources().getDimensionPixelSize(resourceId);  
		// } 
		// return statusBarHeight;
		return 0;
	}

	public static int C2J_SystemSelectFile(String init_dir) {	
		return SystemFileSelect.Open(init_dir);
	}

	public static int C2J_InstallAPK(String file_path) {
		File file = new File(file_path);
		Intent install = new Intent(Intent.ACTION_VIEW);
		install.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);// API 11后才有效
		install.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		install.setDataAndType(Uri.fromFile(file),
				"application/vnd.android.package-archive");
		SDLActivity.getContext().startActivity(install);
		return 0;
	}

	public static int C2J_StartAPP(String package_name) {
		Intent launch = SDLActivity.getContext().getPackageManager()
				.getLaunchIntentForPackage(package_name);
		launch.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
		SDLActivity.getContext().startActivity(launch);
		return 0;
	}

	public static String C2J_GetNetworkType() {
		ConnectivityManager connManager = (ConnectivityManager) SDLActivity.getContext().getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo info = connManager.getActiveNetworkInfo();
		if (info == null || !info.isAvailable()) return "OtherSystem_NotifyNetwork_none";
		int networkType = info.getType();
		if (networkType == ConnectivityManager.TYPE_WIFI) return "OtherSystem_NotifyNetwork_wifi";
		return "OtherSystem_NotifyNetwork_line";
	}
	
	public static String C2J_GetDeviceID()
	{
		TelephonyManager tm = (TelephonyManager)SDLActivity.getContext().getSystemService(Context.TELEPHONY_SERVICE);
		if (tm == null) return "";
		return tm.getDeviceId();
	}

	public static int C2J_MoveTaskToBack()
	{
		SDLActivity.mSingleton.moveTaskToBack(true);
		return 0;
	}

	public static int C2J_OpenUrlBySystemBrowser(String url)
	{
		 Uri  uri = Uri.parse(url);
   		Intent  intent = new Intent(Intent.ACTION_VIEW, uri);
   		SDLActivity.getContext().startActivity(intent);
		return 0;
	}
}
