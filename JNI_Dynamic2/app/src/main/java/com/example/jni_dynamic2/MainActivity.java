package com.example.jni_dynamic2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.jni_dynamic2.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'jni_dynamic2' library on application startup.
    static {
        System.loadLibrary("jni_dynamic2");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        tv.setText("静态注册" + stringFromJNI() + "\n动态注册" + native_hello());
      //  tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'jni_dynamic2' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native String native_hello();
}