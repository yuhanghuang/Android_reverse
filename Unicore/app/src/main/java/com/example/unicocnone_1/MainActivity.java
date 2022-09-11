package com.example.unicocnone_1;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.example.unicocnone_1.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {
    public NdkTest ndkTest;

    // Used to load the 'unicocnone_1' library on application startup.
    static {
        System.loadLibrary("unicocnone_1");
    }

    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // Example of a call to a native method
        TextView tv = binding.sampleText;
        ndkTest = new NdkTest();

       // tv.setText(ndkTest.helloNative());

    }

    /**
     * A native method that is implemented by the 'unicocnone_1' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
//    public native
}