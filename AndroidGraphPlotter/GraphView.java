package com.example.testgraph;


import android.content.Context;
import android.os.Handler;
import android.util.AttributeSet;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ProgressBar;

public class GraphView extends FrameLayout implements Runnable {
    private GraphTemplate template;
    private FrameLayout layout;
    private Handler handler;
    private ProgressBar progressBar;
    private ImageView imageView;
    private GraphPlotter plotter;

    public GraphView(Context context, AttributeSet attrs) {
        super(context, attrs);
        initialize(context);
    }

    private void initialize(Context context){
        template = new GraphTemplate();
        layout = this;
        handler = new Handler();
        progressBar = new ProgressBar(context);
        imageView = new ImageView(context);
        this.setMinimumHeight(350);
        this.setMinimumWidth(300);
    }

    public GraphTemplate getGraphTemplate(){
        return template;
    }

    public void draw(){
        this.addView(imageView);
        this.addView(progressBar);
        Thread process = new Thread(this);
        process.start();
    }

    @Override
    public void run() {
        plotter = new GraphPlotter(template, imageView, layout, handler, progressBar);
    }
}
