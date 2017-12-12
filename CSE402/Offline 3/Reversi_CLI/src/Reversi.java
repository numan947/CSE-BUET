import java.io.*;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

/**
 * Created by numan947 on 12/10/17.
 **/

class GridPosition implements Serializable
{
    private int posR;
    private int posC;

    public GridPosition() {
    }

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
                        if(isValid) {//the cell is valid, i.e we've seen only opposite color cell before this
                            GridPosition gp = new GridPosition(curPosR,curPosC);
                            if(ret.indexOf(gp)==-1) ret.add(gp);
                        }
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
        addToList.add(move);

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
                if(isOutOfTheBoard(curPosR,curPosC)) {
                    toModify.clear();
                    break;
                }

                //potential change element
                else if(this.grid[curPosR][curPosC]==oppositeColor) {
                    GridPosition gp = new GridPosition(curPosR,curPosC);
                    if(toModify.indexOf(gp)==-1)
                        toModify.add(new GridPosition(curPosR, curPosC));
                }

                //nope, we can't go that way
                else if(this.grid[curPosR][curPosC]=='-') {
                    toModify.clear();
                    break;
                }

                //modify all in toModify
                else if(this.grid[curPosR][curPosC]==playerColor){

                    for(GridPosition g: toModify){
                       int idx = removeFromList.indexOf(g);
//                       System.out.println(g);
//                       System.out.println(idx);
//                        System.out.println("RFL : "+removeFromList);
//                        System.out.println("ATL : "+addToList);
//                        System.out.println("TM : "+toModify);
//                        System.out.println("CurrentMove: "+move);
                       removeFromList.remove(idx);
                    }

//                    System.out.println("After Modifying RemoveFromList: ");
//                    System.out.println(removeFromList);

                    addToList.addAll(toModify);
//                    System.out.println("After Modifying AddToList: ");
//                    System.out.println(addToList);
                    break;
                }
            }

            for(GridPosition gp : toModify){
                this.grid[gp.getPosR()][gp.getPosC()] = playerColor;
            }
        }
    }



    public int getFreePositions()
    {
        return (boardSize*boardSize)-getBlackScore()-getBlackScore();
    }

    public int getWhiteScore()
    {
        return this.whiteDisks.size();
    }

    public int getBlackScore()
    {
        return this.blackDisks.size();
    }

    private boolean isOutOfTheBoard(int x, int y)
    {
        return !(x>=0 && x<boardSize && y>=0 && y<boardSize);
    }
    @Override
    public String toString() {
        return printBoard();/*+"\nReversiBoard{\n" +
                "totalDisks=" + totalDisks +
                ",\n blackDisks=" + blackDisks.size() +
                ",\n whiteDisks=" + whiteDisks.size() +
                ",\n boardSize=" + boardSize +
                "\n}";*/
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

    public char[][] getGrid() {
        return grid;
    }

    public ArrayList<GridPosition> getWhiteDisks() {
        return whiteDisks;
    }

    public ArrayList<GridPosition> getBlackDisks() {
        return blackDisks;
    }

    public int getBoardSize()
    {
        return boardSize;
    }
}



class Utils{
    public static int log2(int n)
    {
        return (n==1) ? 0 : 1+log2(n/2);
    }
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

class MiniMaxImplementation{
    private Heuristic heuristic;
    private int maxDepth;

    public MiniMaxImplementation(Heuristic heuristic,int maxDepth) {
        this.heuristic = heuristic;
        this.maxDepth = maxDepth;
    }

    private int minimax(ReversiBoard rv,int depth,boolean maxPlayer,char player,char opponent)
    {
        if(rv.getFreePositions()==0) //no move left
            return 0;

        if(depth==0){
            int h;
            if(maxPlayer) {
                h = heuristic.computeHeuristic(rv, player, opponent);
            }
            else
                h = heuristic.computeHeuristic(rv,opponent,opponent);
            //System.out.println("Computed H For: "+h);
            return h;
        }


        if(maxPlayer){
            ArrayList<GridPosition>moves = rv.findMoves(player);
            int best = Integer.MIN_VALUE;

            for(GridPosition g: moves){
                ReversiBoard crv = (ReversiBoard) Utils.deepClone(rv);

                assert crv != null;
                crv.applyMove(g,player);

                int tmpVal = minimax(crv,depth-1,false,player,opponent);

                if(tmpVal>best){
                    best = tmpVal;
                }
            }
            return best;
        }
        else {
            ArrayList<GridPosition>moves = rv.findMoves(opponent);
            int best = Integer.MAX_VALUE;

            for(GridPosition g:moves){
                ReversiBoard crv = (ReversiBoard) Utils.deepClone(rv);

                assert crv != null;
                crv.applyMove(g,player);

                int tmpVal = minimax(crv,depth-1,true,player,opponent);

                if(tmpVal<best){
                    best = tmpVal;
                }
            }
            return best;
        }
    }




    public GridPosition findBestMove(ReversiBoard reversiBoard,ArrayList<GridPosition>validMoves,char player,char opponent)
    {
        int bestVal = Integer.MIN_VALUE;
        GridPosition bestMove = new GridPosition();

        for(GridPosition g:validMoves){
            ReversiBoard rv = (ReversiBoard) Utils.deepClone(reversiBoard);
            assert rv != null;
            rv.applyMove(g,player);


            int moveVal = minimax(reversiBoard,maxDepth,false,player,opponent);

            if(moveVal>bestVal){
                bestMove.setPosC(g.getPosC());
                bestMove.setPosR(g.getPosR());
                bestVal = moveVal;
            }
        }

        System.out.println("Found Best Move: "+bestMove+" With Value: "+bestVal);

        //todo: fixme
        return bestMove;
    }



}



class PlayFormat{

    public static void PlayerVsPlayer()
    {
        System.out.println("Player Vs Player Initializing.......Black Goes First!!");
        Scanner scanner = new Scanner(System.in);
        ReversiBoard rb = new ReversiBoard(8);
        rb.initializeBoard();
       // System.out.println(rb.toString());

        String curPlayer = "Black";
        String oppPlayer = "White";
        char p = 'B';
        char opp = 'W';

        ArrayList<GridPosition>currentMoves = rb.findMoves(p);

        while (rb.getFreePositions()!=0){

            System.out.println("Trun: "+curPlayer);
            System.out.println("Score: White: "+rb.getWhiteScore()+" Black: "+rb.getBlackScore());
            System.out.println(rb.toString());
            System.out.println("Please select one of the moves"+" "+currentMoves);
            int r,c;
            try{

                String input = scanner.next();
                String[]inp = input.trim().split(",");
                r= Integer.parseInt(inp[0]);
                c = Integer.parseInt(inp[1]);
            }catch (NumberFormatException e){
                System.err.println("WRONG FORMAT!!!");
                continue;
            }


            rb.applyMove(new GridPosition(r,c),p);



            currentMoves = rb.findMoves(opp);

            if(currentMoves.size()>0){//valid move available for opposition
                //swap
                char tmp = opp;
                opp = p;
                p = tmp;

                String tmpPlayer = curPlayer;
                curPlayer = oppPlayer;
                oppPlayer = tmpPlayer;
            }
            else{
                System.err.println("No Moves Available for opposition: "+oppPlayer+"\nContinuing for ...."+curPlayer);
                currentMoves = rb.findMoves(p);
            }
        }
    }


    public static void PlayerVsComputer(Heuristic heuristic,int maxDepth)
    {
        System.out.println("Player Vs Computer Initializing.......");
        Random random = new Random();
        int toss = random.nextInt(1234);

        char player,computer;

        MiniMaxImplementation myMiniMax = new MiniMaxImplementation(heuristic,maxDepth);


        if(toss%2==0){
            player = 'B';
            computer = 'W';
        }
        else{
            player = 'W';
            computer = 'B';
        }

        System.out.println("Player is: "+player+" Computer is: "+computer);

        Scanner scanner = new Scanner(System.in);
        ReversiBoard rb = new ReversiBoard(8);
        rb.initializeBoard();
       // System.out.println(rb.toString());

        String curPlayer = "Black";
        String oppPlayer = "White";
        char p = 'B';
        char opp = 'W';


        ArrayList<GridPosition>currentMoves = rb.findMoves(p);

        while (rb.getFreePositions()!=0){

            System.out.println("Trun: "+curPlayer);
            System.out.println("Score: White: "+rb.getWhiteScore()+" Black: "+rb.getBlackScore());
            System.out.println(rb.toString());
            System.out.println("Please select one of the moves"+" "+currentMoves);
            int r = -1,c = -1;
            GridPosition gp = null;
            if(p==player) {
                //Player MOVE
                try {

                    String input = scanner.next();
                    String[] inp = input.trim().split(",");
                    r = Integer.parseInt(inp[0]);
                    c = Integer.parseInt(inp[1]);
                    gp = new GridPosition(r,c);
                } catch (NumberFormatException e) {
                    System.err.println("WRONG FORMAT!!!");
                    continue;
                }
            }
            else{
                //AI MOVE
                gp = myMiniMax.findBestMove(rb,currentMoves,p,opp);
            }


            rb.applyMove(gp,p);


            currentMoves = rb.findMoves(opp);

            if(currentMoves.size()>0){//valid move available for opposition
                //swap
                char tmp = opp;
                opp = p;
                p = tmp;

                String tmpPlayer = curPlayer;
                curPlayer = oppPlayer;
                oppPlayer = tmpPlayer;
            }
            else{
                System.err.println("No Moves Available for opposition: "+oppPlayer+"\nContinuing for ...."+curPlayer);
                currentMoves = rb.findMoves(p);
            }
        }
    }

    public static void ComputerVsComputer(Heuristic heuristic,int maxDepth)
    {
        System.out.println("Computer Vs Computer Initializing.......");
        Random random = new Random();
        int toss = random.nextInt(1234);

        char computer1,computer2;

        MiniMaxImplementation myMiniMax = new MiniMaxImplementation(heuristic,maxDepth);


        if(toss%2==0){
            computer1 = 'B';
            computer2 = 'W';
        }
        else{
            computer1 = 'W';
            computer2 = 'B';
        }

        System.out.println("Player is: "+computer1+" Computer is: "+computer2);

        Scanner scanner = new Scanner(System.in);
        ReversiBoard rb = new ReversiBoard(8);
        rb.initializeBoard();
        //System.out.println(rb.toString());

        String curPlayer = "Black";
        String oppPlayer = "White";
        char p = 'B';
        char opp = 'W';


        ArrayList<GridPosition>currentMoves = rb.findMoves(p);

        while (rb.getFreePositions()!=0){

            System.out.println("Trun: "+curPlayer);
            System.out.println("Score: White: "+rb.getWhiteScore()+" Black: "+rb.getBlackScore());
            System.out.println(rb.toString());
            System.out.println("Please select one of the moves"+" "+currentMoves);
            int r = -1,c = -1;
            GridPosition gp = myMiniMax.findBestMove(rb,currentMoves,p,opp);
//            if(p==computer1) {
//                //Player MOVE
//                try {
//
//                    String input = scanner.next();
//                    String[] inp = input.trim().split(",");
//                    r = Integer.parseInt(inp[0]);
//                    c = Integer.parseInt(inp[1]);
//                    gp = new GridPosition(r,c);
//                } catch (NumberFormatException e) {
//                    System.err.println("WRONG FORMAT!!!");
//                    continue;
//                }
//            }
//            else{
//                //AI MOVE
//                gp = myMiniMax.findBestMove(rb,currentMoves,p,opp);
//            }


            rb.applyMove(gp,p);

            currentMoves = rb.findMoves(opp);

            if(currentMoves.size()>0){//valid move available for opposition
                //swap
                char tmp = opp;
                opp = p;
                p = tmp;

                String tmpPlayer = curPlayer;
                curPlayer = oppPlayer;
                oppPlayer = tmpPlayer;
            }
            else{
                System.err.println("No Moves Available for opposition: "+oppPlayer+"\nContinuing for ...."+curPlayer);
                currentMoves = rb.findMoves(p);
            }
        }
    }
}
interface Heuristic{
    int computeHeuristic(ReversiBoard rv, char player, char opponent);
}


class PositionalHeuristic1 implements Heuristic{
    private int[][]heurGrid= new int[][]{
            {4,-3,2,2,2,2,-3,4},
            {-3,-4,-1,-1,-1,-1,-4,-3},
            {2,-1,1,0,0,1,-1,2},
            {2,-1,0,1,1,0,-1,2},
            {2,-1,0,1,1,0,-1,2},
            {2,-1,1,0,0,1,-1,2},
            {-3,-4,-1,-1,-1,-1,-4,-3},
            {4,-3,2,2,2,2,-3,4}
    };

    @Override
    public int computeHeuristic(ReversiBoard rv, char player, char opponent) {
        int whiteVal = 0;
        int blackVal = 0;
        for(GridPosition g: rv.getWhiteDisks()){
            whiteVal+=heurGrid[g.getPosR()][g.getPosC()];
        }
        for(GridPosition g: rv.getBlackDisks()){
            blackVal+=heurGrid[g.getPosR()][g.getPosC()];
        }

        if(player=='W')
            return whiteVal-blackVal;
        return blackVal-whiteVal;

    }
}

class PositionalHeuristic2 implements Heuristic{
    private int[][]heurGrid= new int[][]{
            {100,-20,10,5,5,10,-20,100},
            {-20,-50,-2,-2,-2,-2,-50,-20},
            {10,-2,-1,-1,-1,-1,-2,10},
            {5,-2,-1,-1,-1,-1,-2,5},
            {5,-2,-1,-1,-1,-1,-2,5},
            {10,-2,-1,-1,-1,-1,-2,10},
            {-20,-50,-2,-2,-2,-2,-50,-20},
            {100,-20,10,5,5,10,-20,100}
    };

    @Override
    public int computeHeuristic(ReversiBoard rv, char player, char opponent) {
        int whiteVal = 0;
        int blackVal = 0;
        for(GridPosition g: rv.getWhiteDisks()){
            whiteVal+=heurGrid[g.getPosR()][g.getPosC()];
        }
        for(GridPosition g: rv.getBlackDisks()){
            blackVal+=heurGrid[g.getPosR()][g.getPosC()];
        }

        if(player=='W')
            return whiteVal-blackVal;
        return blackVal-whiteVal;

    }
}



class MobilityHeuristic implements Heuristic{
    private static final int W1=10;
    private static final int W2 = 1;
    @Override
    public int computeHeuristic(ReversiBoard rv, char player, char opponent) {
        //count corners
        int cPl = 0;
        int cOp = 0;

        int sz = rv.getBoardSize();

        if(rv.getGrid()[0][0]==player)
            cPl++;
        if(rv.getGrid()[0][0]==opponent)
            cOp++;
        if(rv.getGrid()[0][sz-1]==player)
            cPl++;
        if(rv.getGrid()[0][sz-1]==opponent)
            cOp++;
        if(rv.getGrid()[sz-1][0]==player)
            cPl++;
        if(rv.getGrid()[0][0]==opponent)
            cOp++;
        if(rv.getGrid()[sz-1][sz-1]==player)
            cPl++;
        if(rv.getGrid()[sz-1][sz-1]==player)
            cOp++;


        ArrayList<GridPosition>mPl = rv.findMoves(player);
        ArrayList<GridPosition>mOp = rv.findMoves(opponent);


        return (W1*(cPl-cOp) + W2*(mPl.size() - mOp.size()))/(mPl.size() + mOp.size());
    }
}

class AbsoluteCountHeuristic implements Heuristic{

    @Override
    public int computeHeuristic(ReversiBoard rv, char player, char opponent) {
        if(player=='W')
            return rv.getWhiteScore() - rv.getBlackScore();
        return rv.getBlackScore() - rv.getWhiteScore();
    }
}





public class Reversi
{
    public static void main(String[] args) {
//        PlayFormat.PlayerVsComputer(new PositionalHeuristic1(),4);

        PlayFormat.ComputerVsComputer(new AbsoluteCountHeuristic(),4);
    }
}
