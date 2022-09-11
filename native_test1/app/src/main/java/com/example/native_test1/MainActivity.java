package com.example.native_test1;

import androidx.appcompat.app.AppCompatActivity;
import  com.example.ndk.NativeTest;

import android.os.Bundle;
import android.widget.TextView;

import com.example.native_test1.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native_test1' library on application startup.
    static {
        System.loadLibrary("native_test1");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        NativeTest nativetest = new NativeTest();
        nativetest.init();
      tv.setText(stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native_test1' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}