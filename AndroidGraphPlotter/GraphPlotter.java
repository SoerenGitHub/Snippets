package com.example.testgraph;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Path;
import android.os.Handler;
import android.util.Log;
import android.util.TypedValue;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.ProgressBar;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.core.view.ViewCompat;

public class GraphPlotter implements ViewTreeObserver.OnGlobalLayoutListener, View.OnTouchListener {

    private final static String TAG = "GraphPlotter";
    private GraphTemplate graphTemplate;
    private GraphContainer graphContainer;
    private Context context;
    private Handler handler;
    private ImageView graphimage;
    private FrameLayout layout;
    private ProgressBar ladeanimation;
    //For Drawing
    private Paint paint;
    private Canvas canvas;
    private Bitmap bitmap;
    private Path path;


    public GraphPlotter(@NonNull GraphTemplate graphTemplate, @NonNull ImageView image, @NonNull FrameLayout layout, @Nullable Handler handler, @Nullable ProgressBar ladeanimation){
        synchronized (this){
            initialize(graphTemplate, handler, layout, image, ladeanimation);
        }
    }

    private void initialize(GraphTemplate graphTemplate, Handler handler, FrameLayout layout, ImageView image, ProgressBar ladeanimation){
        this.graphTemplate = graphTemplate;
        this.handler = handler;
        this.graphContainer = new GraphContainer(image, graphTemplate.size());
        this.context = layout.getContext();
        this.paint = new Paint();
        this.layout = layout;
        this.graphimage = image;
        this.ladeanimation = ladeanimation;
        graphimage.setOnTouchListener(this);
        paint.setStrokeWidth(1);
        paint.setAntiAlias(true);
        graphimage.getViewTreeObserver().addOnGlobalLayoutListener(this);
    }

    private void createGridGraphic(){
        paint.setStyle(Paint.Style.STROKE);
        paint.setColor(graphTemplate.getGridlinesColor());
        for(GraphDrawPoint p : graphTemplate){
            canvas.drawLine((int)p.getX()+3, graphContainer.getY()+ graphContainer.getHeight(),
                    (int)p.getX()+3, graphContainer.getY()- graphContainer.getHeight()+5, paint);
        }
    }

    private void createPathFillGraphic(){
        paint.setStyle(Paint.Style.FILL);
        paint.setColor(graphTemplate.getPathFillColor());
        path = new Path();
        if(!graphTemplate.isEmpty()) path.moveTo((int)graphTemplate.get(0).getX()+3, (int)graphTemplate.get(0).getY());
        for(int i = 1; i < graphTemplate.size(); i++){
            path.lineTo((int)graphTemplate.get(i).getX()+3, (int)graphTemplate.get(i).getY());
        }
        path.lineTo((int)graphTemplate.get(graphTemplate.size()-1).getX()+3, graphContainer.getY()+ graphContainer.getHeight());
        path.lineTo((int)graphTemplate.get(0).getX()+3, graphContainer.getY()+ graphContainer.getHeight());
        path.lineTo((int)graphTemplate.get(0).getX()+3, (int)graphTemplate.get(0).getY());
        canvas.drawPath(path, paint);
    }

    private void createPathGraphic(){
        paint.setStyle(Paint.Style.STROKE);
        paint.setColor(graphTemplate.getPathColor());
        path = new Path();
        if(!graphTemplate.isEmpty()) path.moveTo((int)graphTemplate.get(0).getX(), (int)graphTemplate.get(0).getY());

        for(int i = 1; i < graphTemplate.size(); i++){
            path.lineTo((int)graphTemplate.get(i).getX(), (int)graphTemplate.get(i).getY());
        }
        canvas.drawPath(path, paint);
    }

    private void createPointsGraphic(){
        paint.setColor(graphTemplate.getDotColor());
        paint.setStyle(Paint.Style.FILL);
        for(int i = 0; i < graphTemplate.size(); i++){
            canvas.drawCircle((int)graphTemplate.get(i).getX()+2.5f, (int)graphTemplate.get(i).getY(), 5, paint);
        }
    }

    private boolean determineDrawZone(){
            if(graphContainer.getWidth() != 0 && graphContainer.getHeight() != 0){
                bitmap = Bitmap.createBitmap(
                        graphContainer.getWidth(),
                        graphContainer.getHeight(),
                        Bitmap.Config.ARGB_8888
                );
                this.canvas = new Canvas(bitmap);
                return true;
            }else{
                layout.removeView(graphimage);
            }
            return false;
    }

    private void createXDescription(){
        for(int i = 0; i < graphTemplate.size(); i++){
            TextView textView = new TextView(context);
            textView.setText(graphTemplate.getXDescription(i));
            textView.setTextSize(TypedValue.COMPLEX_UNIT_PT, 4);
            textView.setTextColor(graphTemplate.getDescriptionTextColor());
            layout.addView(textView);
            textView.measure(0,0);
            textView.setX((int)graphTemplate.get(i).getX()-(textView.getMeasuredWidth()/2));
            textView.setY(graphContainer.getY()+graphContainer.getHeight()-textView.getMeasuredHeight());
            ViewCompat.setTranslationZ(textView, 1);

        }
    }

    private void createYDescription(int i){
        if(handler != null){
            final TextView textView = new TextView(context);
            textView.setText(String.valueOf(graphTemplate.getYDescription(i)));
            textView.setTextSize(TypedValue.COMPLEX_UNIT_PT, 4);
            textView.setAlpha(0);
            textView.setTextColor(graphTemplate.getDescriptionTextColor());
            layout.addView(textView);
            textView.animate().alpha(1).setDuration(500);
            textView.measure(0,0);
            textView.setX((int)graphTemplate.get(i).getX()-(textView.getMeasuredWidth()/2));
            textView.setY((int)graphTemplate.get(i).getY()-(textView.getMeasuredHeight()+10));
            ViewCompat.setTranslationZ(textView, 1);
            new Thread(new Runnable() {
                @Override
                public void run() {
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        Log.d(TAG, e.getLocalizedMessage());
                    }
                    textView.animate().alpha(0);
                    try {
                        Thread.sleep(2000);
                    } catch (InterruptedException e) {
                        Log.d(TAG, e.getLocalizedMessage());
                    }
                    removeTextView(textView);
                }
            }).start();
        }
    }

    private void removeTextView(final TextView view){
        handler.post(new Runnable() {
            @Override
            public void run() {
                layout.removeView(view);
            }
        });
    }

    @Override
    public boolean onTouch(View view, MotionEvent motionEvent) {
        float xclick = motionEvent.getX();
        for(int i = 0; i < graphTemplate.size(); i++){
            float xpoint = (float) graphTemplate.get(i).getX();
            if (xclick <= xpoint && xclick > xpoint-(graphContainer.getElemDiffer()/2) ||
                    xclick >= xpoint && xclick < xpoint+(graphContainer.getElemDiffer()/2)) {
                createYDescription(i);
            }
        }
        return false;
    }

    @Override
    public void onGlobalLayout() {
        synchronized (this){
            graphContainer.calculate();
            if(determineDrawZone()){
                graphTemplate.calculateDimensions(graphContainer);
                createGridGraphic();
                createPathFillGraphic();
                createPathGraphic();
                createPointsGraphic();
                createXDescription();
                graphimage.getViewTreeObserver().removeGlobalOnLayoutListener( this );
                graphimage.setImageBitmap(bitmap);
                graphimage.setScaleType(ImageView.ScaleType.FIT_XY);
                graphimage.getLayoutParams().width = graphContainer.getWidth();
                graphimage.getLayoutParams().height = graphContainer.getHeight();
                graphimage.setPadding(0,0,0,0);
                if(ladeanimation != null) ladeanimation.setVisibility(View.INVISIBLE);
            }
        }
    }
}

