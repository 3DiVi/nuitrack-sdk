package com.tdv.nuitrack.sdk.samples.NuitrackGLSampleNI;

import java.util.Arrays;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.Intent;
import android.Manifest;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;

import com.tdv.nuitrack.sdk.Nuitrack;

public class NuitrackGLSampleNIActivity extends Activity
{
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

	private void NuitrackInit() {
		Nuitrack.init(this, new Nuitrack.NuitrackCallback() {
			public void onInitSuccess(Context context) {
				Intent intent = new Intent(context, NativeActivity.class);
				startActivity(intent);
				finish();
			}
			public void onInitFailure(int errorId) {}
		});
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

	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
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
}
