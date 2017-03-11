package main;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
import java.util.TimerTask;

/**
 * Created by numan947 on 3/11/17.
 **/
public class MyClock extends TimerTask {
    private Hashtable<Integer,Participant>participantHashtable;
    private Hashtable<String,Exam>examHashtable;


    public MyClock(Hashtable<Integer, Participant> participantHashtable, Hashtable<String,Exam>examHashtable) {
        this.participantHashtable = participantHashtable;
        this.examHashtable=examHashtable;
    }

    @Override
    public void run() {
        Iterator<Map.Entry<Integer, Participant>> iterator=participantHashtable.entrySet().iterator();

        while (iterator.hasNext())
        {
            Map.Entry<Integer,Participant> entry=iterator.next();
            Participant participant=entry.getValue();

            // if the time is not up and the client is not disconnected and the client's exam is started
            if( !participant.isTimeup() && !(participant.isCrashed())
                    && !(participant.getRemainingTimeInSeconds() == -1)){
                Exam e=examHashtable.get(participant.getExamCode());
                int warning=e.getWarningTime()/1000;
                int remTime=participant.getRemainingTimeInSeconds();
                remTime--;
                participant.setRemainingTimeInSeconds(remTime);

                // warning flag set
                if(warning==remTime){
                    participant.getMainNetworkThread().setSendWarningFlag(true);
                }
                else if(remTime==0)participant.getMainNetworkThread().setFinishedExamFlag(true);

                System.out.println("Time remaining: "+remTime);

            }

        }

    }
}
