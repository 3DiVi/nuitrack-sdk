//This file needs to be here so the "ant" build step doesnt fail when looking for a /src folder.

package com.epicgames.ue4;

import java.util.Arrays;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.Manifest;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.view.View;

import com.tdv.nuitrack.sdk.Nuitrack;

public class NuiActivity extends Activity
{
	public static Logger Log = new Logger("UE4");

	private static final int REQUIRED_PERMISSIONS_REQUEST = 0;

	private boolean hasPermissions(Activity activity, String... requiredPermissions) {
		for (String permission : requiredPermissions)
			if (ContextCompat.checkSelfPermission(activity, permission) != PackageManager.PERMISSION_GRANTED)
				return false;
		return true;
	}

	private void requestPermissions(Activity activity, String... requiredPermissions) {
		if (hasPermissions(activity, requiredPermissions))
			NuitrackInit();
		else
			ActivityCompat.requestPermissions(activity, requiredPermissions, REQUIRED_PERMISSIONS_REQUEST);
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
		switch (requestCode) {
			case REQUIRED_PERMISSIONS_REQUEST:
				if (!Arrays.asList(grantResults).contains(PackageManager.PERMISSION_DENIED)) {
					NuitrackInit();
				}
				return;
		}
	}

	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.M) {
			String[] requiredPermissions = {
				Manifest.permission.READ_EXTERNAL_STORAGE,
				Manifest.permission.WRITE_EXTERNAL_STORAGE,
				Manifest.permission.CAMERA
			};
			requestPermissions(this, requiredPermissions);
		}
		else {
			NuitrackInit();
		}
	}

	private void NuitrackInit()
	{
		Log.debug( "Nuitrack init START");
		Nuitrack.init(this, new Nuitrack.NuitrackCallback() {
			public void onInitSuccess(Context context) {
				Log.debug( "Nuitrack init SUCCESS");				
				startGame();
			}
			public void onInitFailure(int errorId) {
				Log.error( "Nuitrack init FAILED");
				finish();
			}
		});
	}
	
	private void startGame()
	{
		Log.debug( "Nuitrack START GAME");

		Intent intent = new Intent(this, SplashActivity.class);
		if (intent.resolveActivityInfo(getPackageManager(), 0) == null)
			intent = new Intent(this, GameActivity.class);

		startActivity(intent);

		finish();
		overridePendingTransition(0, 0);
	}
}