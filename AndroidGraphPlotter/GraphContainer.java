package com.example.testgraph;

import android.widget.ImageView;

public class GraphContainer {
    private ImageView graphcontainer;
    private int elementsize;
    private int width;
    private int height;
    private int x;
    private int y;
    private int elemdiffer;

    public GraphContainer(ImageView graphcontainer, int elementsize){
        initialize(graphcontainer, elementsize);
    }

    private void initialize(ImageView graphzone, int elementsize){
        this.graphcontainer = graphzone;
        this.elementsize = elementsize;
    }

    public void calculate(){
        width = (int)(graphcontainer.getMeasuredWidth());
        height = (int)(graphcontainer.getMeasuredHeight());
        x = (int)graphcontainer.getX();
        y = (int)graphcontainer.getY();
        elemdiffer = (int)width/elementsize;
    }

    public int getElemDiffer(){
        return elemdiffer;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }
}
