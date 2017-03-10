package main;

import java.util.*;

/**
 * Created by numan947 on 3/10/17.
 **/
public class BackupCheckerThread implements Runnable {
    private Hashtable<Integer,Participant> participantHashtable;
    private Server_GUI_Controller controller;
    private ArrayList<Integer>noScheduledBackList;
    private boolean running;

    public BackupCheckerThread(Hashtable<Integer, Participant> participantHashtable, Server_GUI_Controller controller) {
        this.participantHashtable = participantHashtable;
        this.controller = controller;
        this.running=true;
        this.noScheduledBackList=new ArrayList<>();
        Thread thread=new Thread(this);
        thread.setDaemon(true);
        thread.start();
    }

    public void setRunning(boolean running) {
        this.running = running;
    }

    @Override
    public void run() {

        while (running)
        {
            Map map=new HashMap<>(participantHashtable);
            Iterator<Map.Entry<Integer,Participant>>it=map.entrySet().iterator();
            while (it.hasNext()){
                Map.Entry<Integer,Participant>pppp=it.next();
                int roll=pppp.getKey();
                Participant p=pppp.getValue();
                long backuptime=p.getNextScheduledBackup();
                if(backuptime<System.currentTimeMillis()&&backuptime!=-1){
                    noScheduledBackList.add(roll);

                    //set it to -1, so that we don't show it again and again
                    participantHashtable.get(roll).setNextScheduledBackup(-1);
                }
            }
            if(noScheduledBackList.size()>0){
                controller.showErrorDialog(new ArrayList<>(noScheduledBackList));
                noScheduledBackList.clear();
            }


            // do this whole thing again and again after one second of sleep
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }




    }
}
