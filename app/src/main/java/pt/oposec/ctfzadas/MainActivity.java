/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package pt.oposec.ctfzadas;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    final String Open_Sesame = "open_sesame";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        /*
        adb shell am start -n "pt.oposec.ctfzadas/.MainActivity" --es "open_sesame" "https://abc.def/xyzw.html"
         */
        setContentView(R.layout.activity_hello_jni);
        Intent intent = getIntent();
        String url = "https://www.meetup.com/0xOPOSEC/";
        if (intent.hasExtra(Open_Sesame)) {
            url = intent.getStringExtra(Open_Sesame);
        }

        WebView webView = findViewById(R.id.webviewzadas);
        webView.getSettings().setJavaScriptEnabled(true);
        webView.getSettings().setAllowFileAccess(false);
        webView.getSettings().setAppCacheEnabled(false);
        webView.getSettings().setCacheMode(WebSettings.LOAD_NO_CACHE);
        webView.addJavascriptInterface(new CTFObject(), "ctfObj");

        webView.loadUrl(url);

    }


    public native String stringFromJNI();


    static {
        System.loadLibrary("opoctf-jni");
    }
}
