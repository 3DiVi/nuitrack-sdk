//This file needs to be here so the "ant" build step doesnt fail when looking for a /src folder.

package com.epicgames.ue4;

import android.os.Bundle;
import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.view.View;

import com.tdv.nuitrack.sdk.Nuitrack;

public class NuiActivity extends Activity
{
	public static Logger Log = new Logger("UE4");
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

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
		Intent intent = new Intent(this, SplashActivity.class);
		if (intent.resolveActivityInfo(getPackageManager(), 0) == null)
			intent = new Intent(this, GameActivity.class);

		startActivity(intent);

		finish();
		overridePendingTransition(0, 0);
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		finish();
		overridePendingTransition(0, 0);
	}
}