import java.net.InetAddress;
import java.net.UnknownHostException;

/**
 * Created by numan947 on 3/9/17.
 **/
public class TEST {

    public static void main(String[] args) {
        try {
            System.out.println(InetAddress.getByName(null));
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
    }
}
