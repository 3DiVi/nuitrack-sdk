package com.tdv.nuitrack.sdk.samples.NuitrackGLSample;

import android.app.Activity;
import android.content.Context;
import android.app.NativeActivity;
import android.content.Intent;
import android.os.Bundle;

import com.tdv.nuitrack.sdk.Nuitrack;

public class NuitrackGLSampleActivity extends Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        Nuitrack.init(this, new Nuitrack.NuitrackCallback() {
		public void onInitSuccess(Context context) {
			Intent intent = new Intent(context, NativeActivity.class);
			startActivity(intent);
			finish();
		}
		public void onInitFailure(int errorId) {}
	});
    }
}
