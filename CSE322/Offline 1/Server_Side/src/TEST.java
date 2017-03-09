import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Created by numan947 on 3/9/17.
 **/
public class TEST {

    public static void main(String[] args) {
        System.out.println(new File("/home/numan947/Documents/Server/Question/question1.doc").exists());
        System.out.println(new File("/home/numan947/Documents/Server/Question/question1.doc").getName());
        System.out.println(new File("/home/numan947/Documents/Server/Question/question1.doc").getFreeSpace());
        System.out.println(new File("/home/numan947/Documents/Server/Question/question1.doc").getTotalSpace());
        System.out.println(new File("/home/numan947/Documents/Server/Question/question1.doc").length());



    }
}
