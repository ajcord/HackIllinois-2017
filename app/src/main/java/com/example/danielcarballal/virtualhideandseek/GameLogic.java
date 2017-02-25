package com.example.danielcarballal.virtualhideandseek;

import android.support.annotation.NonNull;

import java.util.Collection;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Timer;
import java.util.Date;
import java.util.TimerTask;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.le.ScanResult;

/**
 * Created by danielcarballal on 25-2-17.
 */

public class GameLogic {
    // Hash map of strings representing players and their respective distances

    int numPlayers;
    public HashMap<String, Integer> playerDists;
    public HashMap<String, Boolean> players; // Boolean checks if the player is a hider or seeker
    public HashMap<String, Long> timeStamp;
    public Timer time;
    Date date = new Date();

    public GameLogic(int numPlayers){
        this.numPlayers = numPlayers;
    }

    public GameLogic(){
        this.numPlayers = 0;
        players = new HashMap<String, Boolean>();
    }

    public String getPlayer(ScanResult result){
        BluetoothDevice device = result.getDevice();
        long newTime = date.getTime();
        timeStamp.put(device.getAddress(), newTime);
        return device.getAddress();
    }

    public void addPlayer(String playerId){
        this.numPlayers++;
        players.put(playerId, false);
    }

    public void updateTime(ScanResult result){
        BluetoothDevice device = result.getDevice();
        String pid = device.getAddress();
        long newTime = date.getTime();
        timeStamp.put(pid, newTime);
    }

    public void checkPlayers(){
        long newTime = date.getTime();
        for (String key : timeStamp.keySet()){
            if(newTime - timeStamp.get(key) >= 20){
                timeStamp.remove(key);
            }
        }
    }

    public void endGame(){
        time.cancel();
        System.out.println("Game ends.");
    }

    public void startGame(){
        time = new Timer();
        time.schedule(new TimerTask() {
            @Override
            public void run() {
                time.cancel();
                System.out.println("Game ends");
            }
        }, 300000);
    }

    public void addLocation(String playerId, int distance) {
        playerDists.put(playerId, distance);
    }
}
