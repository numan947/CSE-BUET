import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

/**
 * Created by numan947 on 12/10/17.
 **/

class GridPosition implements Serializable
{
    private int posR;
    private int posC;

    public GridPosition(int posR, int posC) {
        this.posR = posR;
        this.posC = posC;
    }

    public int getPosR() {
        return posR;
    }

    public void setPosR(int posR) {
        this.posR = posR;
    }

    public int getPosC() {
        return posC;
    }

    public void setPosC(int posC) {
        this.posC = posC;
    }

    @Override
    public String toString() {
        return
                "(" + posR +
                "," + posC +")";
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        GridPosition that = (GridPosition) o;

        return posR == that.posR && posC == that.posC;
    }

    @Override
    public int hashCode() {
        int result = posR;
        result = 31 * result + posC;
        return result;
    }
}



class ReversiBoard implements Serializable{

    private int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    private int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    private int totalDisks;
    private ArrayList<GridPosition>whiteDisks;
    private ArrayList<GridPosition>blackDisks;
    private char[][] grid;
    private int boardSize;
    public ReversiBoard(int size)
    {
        this.totalDisks = 0;
        this.grid= new char[size][size];
        this.whiteDisks = new ArrayList<>();
        this.blackDisks = new ArrayList<>();
        this.boardSize = size;
    }
    public void initializeBoard()
    {
        //empty initialize
        for(int i=0;i<boardSize;i++)
            for(int j=0;j<boardSize;j++)
                this.grid[i][j]='-';

        int val1 = boardSize/2 -1 ;
        int val2 = boardSize/2;

        this.grid[val1][val1] = 'W';
        this.grid[val2][val2] = 'W';
        this.grid[val1][val2] = 'B';
        this.grid[val2][val1] = 'B';

        this.totalDisks = 4;

        this.whiteDisks.add(new GridPosition(val1,val1));
        this.whiteDisks.add(new GridPosition(val2,val2));
        this.blackDisks.add(new GridPosition(val1,val2));
        this.blackDisks.add(new GridPosition(val2,val1));
    }
    public ArrayList<GridPosition> findMoves(char playerColor){
        ArrayList<GridPosition>ret = new ArrayList<>();

        ArrayList<GridPosition>toSearch;
        char oppositeColor;
        if(playerColor=='W'){
            oppositeColor = 'B';
            toSearch = this.whiteDisks;
        }
        else{
            oppositeColor = 'W';
            toSearch = this.blackDisks;
        }

        //search starts here
        //need to find '-', so that it has disk of playerColor in some line, with opposite color disk in between

        for(GridPosition diskPos:toSearch){
            //try 8 directional moves
            for(int i=0;i<8;i++){
                //get the position of the current disk
                int curPosR = diskPos.getPosR();
                int curPosC = diskPos.getPosC();

                //get the current direction
                int curDirR = dx[i];
                int curDirC = dy[i];

                //try moving until break
                boolean isValid = false;
                while (true){
                    curPosR += curDirR;
                    curPosC += curDirC;
                    //we're out of the board
                    //or
                    //we've seen a player color disk, starting from a player color disk, so this direction is invalid for the disk
                    if(isOutOfTheBoard(curPosR,curPosC) || this.grid[curPosR][curPosC]==playerColor)
                        break;

                    else if(this.grid[curPosR][curPosC]==oppositeColor)
                        isValid = true;

                    else if(this.grid[curPosR][curPosC]=='-'){ //we found an empty cell
                        if(isValid)//the cell is valid, i.e we've seen only opposite color cell before this
                            ret.add(new GridPosition(curPosR,curPosC));
                        break; //not valid, we didn't see any opposite color cell before this
                    }
                }
            }
        }

        return  ret;
    }


    public void applyMove(GridPosition move,char playerColor)
    {
        ArrayList<GridPosition>removeFromList;
        ArrayList<GridPosition>addToList;
        char oppositeColor;
        if(playerColor=='W'){
            oppositeColor = 'B';
            removeFromList = this.blackDisks;
            addToList = this.whiteDisks;
        }
        else {
            oppositeColor = 'W';
            removeFromList = this.whiteDisks;
            addToList = this.blackDisks;
        }

        //update the blank position
        this.grid[move.getPosR()][move.getPosC()] = playerColor;

        //8 directional update
        ArrayList<GridPosition>toModify = new ArrayList<>();

        for(int i=0;i<8;i++){
            //get the position of the current disk
            int curPosR = move.getPosR();
            int curPosC = move.getPosC();

            //get the current direction
            int curDirR = dx[i];
            int curDirC = dy[i];

            toModify.clear();

            while (true){
                curPosR += curDirR;
                curPosC += curDirC;
                //we're out of the board
                if(isOutOfTheBoard(curPosR,curPosC))
                    break;

                //potential change element
                else if(this.grid[curPosR][curPosC]==oppositeColor)
                    toModify.add(new GridPosition(curPosR,curPosC));

                //nope, we can't go that way
                else if(this.grid[curPosR][curPosC]=='-') {
                    toModify.clear();
                    break;
                }

                //modify all in toModify
                else if(this.grid[curPosR][curPosC]==playerColor){
                    removeFromList.remove(toModify);
                    addToList.addAll(toModify);
                    break;
                }
            }

            for(GridPosition gp : toModify){
                this.grid[gp.getPosR()][gp.getPosC()] = playerColor;
            }
        }
    }





    private boolean isOutOfTheBoard(int x, int y)
    {
        return !(x>=0 && x<boardSize && y>=0 && y<boardSize);
    }
    @Override
    public String toString() {
        return printBoard()+"\nReversiBoard{\n" +
                "totalDisks=" + totalDisks +
                ",\n blackDisks=" + blackDisks.size() +
                ",\n whiteDisks=" + whiteDisks.size() +
                ",\n boardSize=" + boardSize +
                "\n}";
    }
    private String printBoard()
    {
        String s = "  0";

        for(int i=1;i<boardSize;i++)
            s+=" "+i;
        s+="\n";

        for(int i=0;i<boardSize;i++){
            s+=i;
            for(int j =0;j<boardSize;j++){
                s+=" "+grid[i][j];
            }
            s+="\n";
        }
        return s;
    }
}



class Utils{
    public static Object deepClone(Object object)
    {
        try {
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            ObjectOutputStream oos = new ObjectOutputStream(baos);

            oos.writeObject(object);

            ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());
            ObjectInputStream ois = new ObjectInputStream(bais);
            return ois.readObject();

        } catch (IOException | ClassNotFoundException e) {
            e.printStackTrace();
        }
        return null;
    }
}






public class Reversi
{
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        ReversiBoard rb = new ReversiBoard(8);
        rb.initializeBoard();
        System.out.println(rb.toString());

        String player = "Black";

        while (true){

            System.out.println("Please select one of the moves"+" "+rb.findMoves('W'));

            String input = scanner.next("^[0-9]+,[0-9]+");

            String[]inp = input.trim().split(",");

            rb.applyMove(new GridPosition(Integer.parseInt(inp[0]),Integer.parseInt(inp[1])),'W');

            System.out.println(rb.toString());

        }

    }
}
