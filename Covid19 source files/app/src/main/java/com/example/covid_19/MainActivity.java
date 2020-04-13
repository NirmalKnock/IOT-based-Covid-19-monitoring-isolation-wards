package com.example.covid_19;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {
    private Button moisture, temperature, Humidity, Matlab;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);



        temperature = findViewById(R.id.idtemp);
        temperature.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                System.out.println("Button Clicked");

                Intent intent = new Intent(getApplicationContext(), Temperature.class);
                startActivity(intent);
            }
        });


        Humidity = findViewById(R.id.idhum);
        Humidity.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                System.out.println("Button Clicked");

                Intent intent = new Intent(getApplicationContext(), Humidity.class);
                startActivity(intent);
            }
        });



        Matlab = findViewById(R.id.idmat);
        Matlab.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                System.out.println("Button Clicked");

                Intent intent = new Intent(getApplicationContext(), Matlabanalysis.class);
                startActivity(intent);
            }
        });
    }
}
