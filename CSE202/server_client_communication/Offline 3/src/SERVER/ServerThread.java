package SERVER;

import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.cell.TextFieldTableCell;
import javafx.util.Callback;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Hashtable;

public class ServerThread implements Runnable{

    @FXML
    private TableView<Person> Table;

    @FXML
    private TextArea messageBox;



    private Hashtable <String,NetworkUtil> socketMap;
    private int portNumber;
    private ServerSocket servsc;
    private Thread T;


    void SETPORT(int portNumber)
    {
        this.portNumber=portNumber;
    }



    void RUN()
    {
        T=new Thread(this);
        T.start();
    }



    @Override
    public void run() {
        socketMap=new Hashtable<>();
        try {
            servsc=new ServerSocket(portNumber);
        } catch (IOException e) {
            e.printStackTrace();
        }

        while(true){
            Socket cs= null;
            try {
                cs = servsc.accept();
                NetworkUtil client=new NetworkUtil(cs);
                String name= (String) client.read();
                socketMap.put(name,client);
                addClient(name);
            } catch (IOException e) {
                System.out.println("problem in ServerThread/ accepting problem or threading problem "+e);
            }
        }
    }



    public void initializeColumns() {

        TableColumn<Person, String> nameCol = new TableColumn<>("Name");
        nameCol.setMinWidth(100);
        nameCol.setCellValueFactory(new PropertyValueFactory<>("name"));
        nameCol.setCellFactory(TextFieldTableCell.<Person>forTableColumn());

        TableColumn<Person, String> actionCol = new TableColumn<>("Action");
        actionCol.setCellValueFactory(new PropertyValueFactory<>("action"));

        Callback<TableColumn<Person, String>, TableCell<Person, String>> cellFactory =
                param -> {
                    final TableCell<Person, String> cell = new TableCell<Person, String>() {
                        Button btn=new Button("send");
                        @Override
                        public void updateItem(String item, boolean empty) {
                            // action of 'send' button click
                            btn.setOnAction( ( ActionEvent event ) -> {
                                String msg=messageBox.getText();
                                Person person=getTableView().getItems().get(getIndex());
                                String pname=person.getName();
                                NetworkUtil writer=socketMap.get(pname);
                                writer.write(msg);
                                removeClient(person);
                                messageBox.clear();
                            });
                            if(!empty)
                            {
                                setGraphic(btn);
                                setText(null);
                            }
                            else setGraphic(null);
                        }
                    };
                    return cell;
                };
        actionCol.setCellFactory(cellFactory);
        Table.getColumns().addAll(nameCol,actionCol);

    }



    void addClient(String name)
    {
        Person pp=new Person();
        pp.setName(name);
        Table.getItems().add(pp);
    }



    void removeClient(Person person)
    {
        ObservableList<Person>clientList;
        clientList=Table.getItems();
        clientList.remove(person);
    }
}

