package com.example.testgraph;

import android.graphics.Color;

import java.util.ArrayList;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

public class GraphTemplate extends ArrayList<GraphDrawPoint> {
    private ArrayList<String> xdescriptions;
    private ArrayList<String> ydescriptions;
    private int dotcolor;
    private int pathcolor;
    private int pathfillcolor;
    private int gridlinescolor;
    private int backgroundcolor;
    private int descriptiontextcolor;
    private int padding;


    public GraphTemplate(){
        initialize();
    }

    private void initialize(){
        this.xdescriptions = new ArrayList<>();
        this.ydescriptions = new ArrayList<>();
        this.padding = 0;

        determineDefaultColors();
    }

    private void determineDefaultColors(){
        this.dotcolor = Color.parseColor("#2C8DF7");
        this.pathcolor = Color.parseColor("#70B6F8");
        this.pathfillcolor = Color.parseColor("#2DA8D6FF");
        this.gridlinescolor = Color.parseColor("#D1D1D1");
        this.backgroundcolor = Color.WHITE;
        this.descriptiontextcolor = Color.BLACK;
    }

    @Override
    public boolean add(GraphDrawPoint point) {
        return (super.add(point) &&
                xdescriptions.add(null) &&
                ydescriptions.add(null));
    }

    public boolean addPoint(@NonNull GraphDrawPoint point, @Nullable String xdescription, @Nullable String ydescription){
        return (super.add(point) &&
                xdescriptions.add(xdescription) &&
                ydescriptions.add(ydescription));
    }

    public @NonNull
    GraphDrawPoint getPoint(int index){
        return super.get(index);
    }

    public @Nullable
    String getXDescription(int index){
        return xdescriptions.get(index);
    }

    public @Nullable
    String getYDescription(int index){
        return ydescriptions.get(index);
    }

    public void calculateDimensions(GraphContainer graphContainer){
        int xdescriptionpuffer = 50;
        for(GraphDrawPoint point : this){
            point.setX((graphContainer.getWidth() * point.getX())+(graphContainer.getElemDiffer()/2));
            point.setY((graphContainer.getHeight() + (-((graphContainer.getHeight()-(2*padding)-xdescriptionpuffer) * point.getY())))-padding-xdescriptionpuffer);
        }

    }

    public void setXdescriptions(ArrayList<String> xdescriptions) {
        this.xdescriptions = xdescriptions;
    }

    public void setYdescriptions(ArrayList<String> ydescriptions) {
        this.ydescriptions = ydescriptions;
    }

    public void setDotColor(int dotcolor) {
        this.dotcolor = dotcolor;
    }

    public void setPathColor(int pathcolor) {
        this.pathcolor = pathcolor;
    }

    public void setPathfillColor(int pathfillcolor) {
        this.pathfillcolor = pathfillcolor;
    }

    public void setGridlinesColor(int gridlinescolor) {
        this.gridlinescolor = gridlinescolor;
    }

    public void setBackgroundColor(int background) {
        this.backgroundcolor = background;
    }

    public void setPadding(int padding) {
        this.padding = padding;
    }

    public int getPadding() {
        return padding;
    }

    public ArrayList<String> getXdescriptions() {
        return xdescriptions;
    }

    public ArrayList<String> getYdescriptions() {
        return ydescriptions;
    }

    public int getDotColor() {
        return dotcolor;
    }

    public int getPathColor() {
        return pathcolor;
    }

    public int getPathFillColor() {
        return pathfillcolor;
    }

    public int getGridlinesColor() {
        return gridlinescolor;
    }

    public int getBackgroundColor() {
        return backgroundcolor;
    }

    public int getDescriptionTextColor() {
        return descriptiontextcolor;
    }

    public void setDescriptionTextColor(int descriptiontextcolor) {
        this.descriptiontextcolor = descriptiontextcolor;
    }

}
