package com.example.testgraph;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        test();
    }

    private void test(){
        GraphView graphView = findViewById(R.id.graphview);
        for (double i = 0; i < 0.8; i+=0.05){
                GraphDrawPoint graphDrawPoint = new GraphDrawPoint(i,((i*0.6)%(0.2/i)));
                graphView.getGraphTemplate().addPoint(graphDrawPoint, String.valueOf(i).substring(0,3), "Franz");
        }
        GraphDrawPoint graphDrawPoint = new GraphDrawPoint(0.9,0.8);
        graphView.getGraphTemplate().addPoint(graphDrawPoint, "1", "Peter");
        graphView.draw();
    }
}
