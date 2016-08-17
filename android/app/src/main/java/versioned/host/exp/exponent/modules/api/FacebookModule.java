// Copyright 2015-present 650 Industries. All rights reserved.

package versioned.host.exp.exponent.modules.api;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;

import com.facebook.AccessToken;
import com.facebook.CallbackManager;
import com.facebook.FacebookCallback;
import com.facebook.FacebookException;
import com.facebook.FacebookSdk;
import com.facebook.login.LoginManager;
import com.facebook.login.LoginResult;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import com.facebook.react.bridge.Arguments;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.ReadableArray;
import com.facebook.react.bridge.ReadableMap;
import com.facebook.react.bridge.WritableMap;
import host.exp.exponent.ActivityResultDelegator;
import host.exp.exponent.ActivityResultListener;

public class FacebookModule extends ReactContextBaseJavaModule implements ActivityResultListener {
  private final ActivityResultDelegator mDelegatorActivity;
  private CallbackManager mCallbackManager;

  public FacebookModule(ReactApplicationContext reactContext, ActivityResultDelegator delegator, Context context) {
    super(reactContext);

    mDelegatorActivity = delegator;
    mDelegatorActivity.addActivityResultListener(this);

    FacebookSdk.sdkInitialize(context);
    mCallbackManager = CallbackManager.Factory.create();
  }

  @Override
  public String getName() {
    return "ExponentFacebook";
  }

  @ReactMethod
  public void logInWithReadPermissionsAsync(final String appId, final ReadableMap config, final Promise promise) {
    AccessToken.setCurrentAccessToken(null);
    FacebookSdk.setApplicationId(appId);

    List<String> permissions;
    if (config.hasKey("permissions")) {
      permissions = new ArrayList<>();
      ReadableArray ps = config.getArray("permissions");
      for (int i = 0; i < ps.size(); ++i) {
        permissions.add(ps.getString(i));
      }
    } else {
      permissions = Arrays.asList("public_profile", "email", "user_friends");
    }

    LoginManager.getInstance().registerCallback(mCallbackManager, new FacebookCallback<LoginResult>() {
      @Override
      public void onSuccess(LoginResult loginResult) {
        LoginManager.getInstance().registerCallback(mCallbackManager, null);

        // This is the only route through which we send an access token back. Make sure the
        // application ID is correct.
        if (!appId.equals(loginResult.getAccessToken().getApplicationId())) {
          promise.reject(new IllegalStateException("Logged into wrong app, try again?"));
          return;
        }
        WritableMap response = Arguments.createMap();
        response.putString("type", "success");
        response.putString("token", loginResult.getAccessToken().getToken());
        response.putInt("expires", (int) (loginResult.getAccessToken().getExpires().getTime() / 1000));
        promise.resolve(response);
      }

      @Override
      public void onCancel() {
        LoginManager.getInstance().registerCallback(mCallbackManager, null);

        WritableMap response = Arguments.createMap();
        response.putString("type", "cancel");
        promise.resolve(response);
      }

      @Override
      public void onError(FacebookException error) {
        LoginManager.getInstance().registerCallback(mCallbackManager, null);

        promise.reject(error);
      }
    });
    LoginManager.getInstance().logInWithReadPermissions((Activity) mDelegatorActivity, permissions);
  }

  @Override
  public void onActivityResult(final int requestCode, final int resultCode, final Intent data) {
    mCallbackManager.onActivityResult(requestCode, resultCode, data);
  }
}
