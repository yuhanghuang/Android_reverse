package com.example.native_test2;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;
import android.widget.Toast;

import com.example.native_test2.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native_test2' library on application startup.
    static {
        Log.d("11111","222222");
        System.loadLibrary("native_test2");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        Log.d("11111","33333");
//        Toast.makeText(this,str,Toast.LENGTH_SHORT).show();

        // Example of a call to a native method
//        TextView tv = binding.sampleText;
//        tv.setText(stringFromJNI());
        Myjni myjni = new Myjni();
        Log.d("1111111", myjni.native_add(8,9) + "");
    }

    /**
     * A native method that is implemented by the 'native_test2' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}