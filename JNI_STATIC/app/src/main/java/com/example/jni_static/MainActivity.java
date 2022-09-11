package com.example.jni_static;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.jni_static.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jni_static' library on application startup.
    static {
        System.loadLibrary("jni_static");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;

        //tv.setText(native_hello());
        tv.setText("静态注册"+stringFromJNI()+"\n动态注册"+native_hello());
    }

    /**
     * A native method that is implemented by the 'jni_static' native library,
     * which is packaged with this application.
     */

}