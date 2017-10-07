import java.io.*;
import java.util.*;

/**
 * Created by numan947 on 10/7/17.
 **/

interface Heuristic{
    double calculate(int[][]start_state,int[][]goal_state);
}




class Cube{
    private double hval;
    private int depth;
    private Cube parent;
    private int dimension;
    private int[][] currentState;
    private int[][] goalState;
    private ArrayList<int[][]> goalStates;
    private String move;


    public Cube(int[][] currentState, int[][] goalState) {
        this.currentState = currentState;
        this.goalState = goalState;

        this.goalStates = new ArrayList<>();
        this.goalStates.add(goalState);
        int[][]dum = deepCopy(goalState);
        rotateCube(dum);
        this.goalStates.add(dum);
        dum=deepCopy(dum);
        rotateCube(dum);
        this.goalStates.add(dum);
        dum=deepCopy(dum);
        rotateCube(dum);
        this.goalStates.add(dum);



        this.hval = 0;
        this.depth = 0;
        this.parent = null;
        this.dimension = goalState.length;
        this.move = null;
    }


    public Cube(int[][] currentState, int[][] goalState,ArrayList<int[][]>goalStates) {
        this.currentState = currentState;
        this.goalState = goalState;
        this.goalStates = goalStates;


        this.hval = 0;
        this.depth = 0;
        this.parent = null;
        this.dimension = goalState.length;
        this.move = null;
    }

    public Cube deepCopy()
    {
        //working
        int[][]CS = new int[this.dimension][];
        //int[][]GS = new int[this.dimension][];

        for(int i=0;i<this.dimension;i++){
            CS[i] = Arrays.copyOf(currentState[i],currentState[i].length);
            //GS[i] = Arrays.copyOf(goalState[i],goalState[i].length);
        }

        return new Cube(CS,this.goalState);
    }

    /*Methods involving the actual A* algorithm starts here*/

    public ArrayList<Cube> solve(Heuristic heuristic,boolean...multiGoals){

        //working though the same problem as before remains

        boolean mult = false;

        if(multiGoals.length>0)
            mult = true;

        long currenTime = System.currentTimeMillis();


        ArrayList<Cube>closed = new ArrayList<>();
        ArrayList<Cube>priorityQueue = new ArrayList<>();


        int exploration_count = 0;

        priorityQueue.add(this);

        while (!priorityQueue.isEmpty()){
            Cube c = priorityQueue.remove(0);

            exploration_count++;

//            if(closed.size()%100==0){
//                System.out.println("PQ Length: "+priorityQueue.size());
//                System.out.println("Visited Length: "+closed.size());
//                System.out.println("Explored Length: "+exploration_count);
//                System.out.println("Time:"+(System.currentTimeMillis()-currenTime)/1000.0);
//            }

            //System.out.println(c.getDepth()+"  "+c.getHval()+"  "+(c.getHval()+c.getDepth()));


            if(!mult) {
                if (Arrays.deepEquals(c.getCurrentState(), goalState)) {
                    //done

                    System.out.println("Done After Total Exploration: " + exploration_count);
                    System.out.println("Time:" + (System.currentTimeMillis() - currenTime) / 1000.0);
                    if (closed.size() > 0) {
                        return c.generateSolution(new ArrayList<>());
                    } else return new ArrayList<>(); //empty
                }
            }
            else {
                boolean ret =false;
                int[][]cur = c.getCurrentState();
                for(int[][]st:goalStates){
                    if(Arrays.deepEquals(cur,st)){
                        ret =true;
                        break;
                    }
                }

                if(ret){
                    //done
                    System.out.println("Done After Total Exploration: " + exploration_count);
                    System.out.println("Time:" + (System.currentTimeMillis() - currenTime) / 1000.0);
                    if (closed.size() > 0) {
                        return c.generateSolution(new ArrayList<>());
                    } else return new ArrayList<>(); //empty
                }
            }

            ArrayList<Cube>neighbours = c.generateMoves(this.getMove());

            for(Cube cc:neighbours){
                if(!closed.contains(cc) && !priorityQueue.contains(cc)) {

                    if(mult) {
                        double heur = 1000000.0;
                        for (int[][] goal : goalStates) {
                            heur = Math.min(heur, heuristic.calculate(cc.getCurrentState(), goal));
                        }
                        cc.setHval(heur);
                    }
                    else
                        cc.setHval(heuristic.calculate(cc.getCurrentState(),this.goalState));
                    priorityQueue.add(cc);
                }
            }

            closed.add(c);
            priorityQueue.sort((o1, o2) -> {
                if ((o2.getDepth() + o2.getHval()) < (o1.getDepth() + o1.getHval()))
                    return 1;
                if ((o2.getDepth() + o2.getHval()) > (o1.getDepth() + o1.getHval()))
                    return -1;
                if ((o2.getDepth() + o2.getHval()) == (o1.getDepth() + o1.getHval()) && (o2.getDepth() < o1.getDepth())) {
                    return 1;
                }

                return 0;

            });
        }

        System.out.println("Returing NULL");
        return null; //shouldn't reach it
    }


    public ArrayList<Cube> generateSolution(ArrayList<Cube>path)
    {
        if(this.parent==null){
            //Root reached
            return path;
        }
        path.add(this);
        return this.parent.generateSolution(path);
    }





    /*Methods involving operations on Cube starts here*/

    void rotateCube(int mat[][]) {

        int len = mat.length;

        for (int i = 0; i < len / 2; i++) {
            for (int j=i;j<len-i-1;j++) {
                int temp = mat[i][j];
                mat[i][j] = mat[j][len - 1 - i];
                mat[j][len-1-i] = mat[len-1-i][len-1-j];
                mat[len-1-i][len-1-j] = mat[len-1-j][i];
                mat[len-1-j][i] = temp;
            }
        }
    }

    int[][]deepCopy(int mat[][])
    {
        int len = mat.length;
        int [][]copy = new int[len][];
        for(int i=0;i<len;i++)
            copy[i]=Arrays.copyOf(mat[i],mat[i].length);
        return copy;
    }

     void moveLeft(int row){
        //passed test
        int tmp = currentState[row][0];
        System.arraycopy(currentState[row], 1, currentState[row], 0, dimension - 1);
        currentState[row][dimension-1] = tmp;
    }
     void moveRight(int row){
         //passed test
        int tmp = currentState[row][dimension-1];
        System.arraycopy(currentState[row], 0, currentState[row], 1, dimension - 1);
        currentState[row][0]=tmp;
    }
     void moveUp(int col){
        //  passed test
         int tmp = currentState[0][col];
         for(int i=0;i<dimension-1;i++){
             currentState[i][col] = currentState[i+1][col];
         }
         currentState[dimension-1][col]=tmp;
    }
     void moveDown(int col){
        // passed test
         int tmp = currentState[dimension-1][col];
         for(int i=dimension-1;i>0;i--){
             currentState[i][col] = currentState[i-1][col];
         }
         currentState[0][col]=tmp;
    }

    ArrayList<Cube> generateMoves(String move){

        String mv = null;
        if(move==null)
            mv ="ALL";

        ArrayList<Cube>neighbours = new ArrayList<>();
        int newDepth = this.depth+1;
        for(int i=0;i<dimension;i++){
            Cube cube = null;

            //Left Move
            if(mv!=null)
            if(mv.equals("ALL")) {
                cube = deepCopy();
                cube.moveLeft(i);
                cube.setDepth(newDepth);
                cube.setMove("L" + i);
                cube.setParent(this);
                cube.setGoalStates(this.getGoalStates());
                neighbours.add(cube);


                //Right Move
                cube = deepCopy();
                cube.moveRight(i);
                cube.setDepth(newDepth);
                cube.setMove("R" + i);
                cube.setParent(this);
                cube.setGoalStates(this.getGoalStates());
                neighbours.add(cube);

                //Up Move
                cube = deepCopy();
                cube.moveUp(i);
                cube.setDepth(newDepth);
                cube.setMove("U" + i);
                cube.setParent(this);
                cube.setGoalStates(this.getGoalStates());
                neighbours.add(cube);

                //Down Move
                cube = deepCopy();
                cube.moveDown(i);
                cube.setDepth(newDepth);
                cube.setMove("D" + i);
                cube.setGoalStates(this.getGoalStates());
                cube.setParent(this);
                neighbours.add(cube);
            }
            else{
                if(move.charAt(0)!='R'&&Integer.parseInt(String.valueOf(move.charAt(1)))!=i) {
                    cube = deepCopy();
                    cube.moveLeft(i);
                    cube.setDepth(newDepth);
                    cube.setMove("L" + i);
                    cube.setParent(this);
                    cube.setGoalStates(this.getGoalStates());
                    neighbours.add(cube);
                }


                //Right Move
                if(move.charAt(0)!='L'&&Integer.parseInt(String.valueOf(move.charAt(1)))!=i) {
                    cube = deepCopy();
                    cube.moveRight(i);
                    cube.setDepth(newDepth);
                    cube.setGoalStates(this.getGoalStates());
                    cube.setMove("R" + i);
                    cube.setParent(this);
                    neighbours.add(cube);
                }

                //Up Move
                if(move.charAt(0)!='D'&&Integer.parseInt(String.valueOf(move.charAt(1)))!=i) {
                    cube = deepCopy();
                    cube.moveUp(i);
                    cube.setDepth(newDepth);
                    cube.setMove("U" + i);
                    cube.setParent(this);
                    cube.setGoalStates(this.getGoalStates());
                    neighbours.add(cube);
                }

                //Down Move
                if(move.charAt(0)!='U'&&Integer.parseInt(String.valueOf(move.charAt(1)))!=i) {
                    cube = deepCopy();
                    cube.moveDown(i);
                    cube.setDepth(newDepth);
                    cube.setMove("D" + i);
                    cube.setParent(this);
                    cube.setGoalStates(this.getGoalStates());
                    neighbours.add(cube);
                }
            }
        }
        return neighbours;
    }



    /*Methods involving printing starts here*/
    @Override
    public String toString() {

        StringBuilder cur = new StringBuilder("");
        StringBuilder gol = new StringBuilder("");

        for(int i =0;i<dimension;i++){
            cur.append(Arrays.toString(currentState[i])).append("\n");
            gol.append(Arrays.toString(goalState[i])).append("\n");
        }

        String m = null;
        if(move==null)m = "no move";
        else m= move;


        return "Cube{" +"\n"+
                "hval=" + hval +"\n"+
                "depth=" + depth +"\n"+
                "dimension=" + dimension +"\n"+
                "currentState=\n" + cur.toString() +"\n"+
                "goalState=\n\n" + gol.toString() +"\n"+
                "move='" + m + "\n"+
                '}';
    }



    public String printParent()
    {
        if(parent==null)
            return "This is supposed to be ROOT";
        StringBuilder s = new StringBuilder("");
        int[][]parentState = parent.getCurrentState();

        for(int i=0;i<dimension;i++){
            s.append(Arrays.toString(parentState[i])).append("\n");
        }

        return s.toString();
    }

    public String printCurrentState(){
        StringBuilder s = new StringBuilder("");
        for(int i=0;i<dimension;i++){
            s.append(Arrays.toString(currentState[i])).append("\n");
        }
        return s.toString();
    }

    public String printMoveOnParent(){
        if(move==null)
            return "This is supposed to be ROOT";

        StringBuilder sb = new StringBuilder();

        switch (move.charAt(0)){
            case 'R':
                sb.append("Rotate Right : ").append(" Row ").append(move.charAt(1));
                break;
            case 'L':
                sb.append("Rotate Left : ").append(" Row ").append(move.charAt(1));
                break;
            case 'U':
                sb.append("Rotate Up : ").append(" Column ").append(move.charAt(1));
                break;
            case 'D':
                sb.append("Rotate Down : ").append(" Column ").append(move.charAt(1));
                break;
        }
        return sb.toString();
    }

    public int[][] getCurrentState() {
        return currentState;
    }

    @Override
    public boolean equals(Object obj) {

        return obj == this || obj instanceof Cube && Arrays.deepEquals(currentState, ((Cube) obj).currentState);
    }

    public double getHval() {
        return hval;
    }

    public void setHval(double hval) {
        this.hval = hval;
    }

    public int getDepth() {
        return depth;
    }

    public void setDepth(int depth) {
        this.depth = depth;
    }

    public Cube getParent() {
        return parent;
    }

    public void setParent(Cube parent) {
        this.parent = parent;
    }

    public int getDimension() {
        return dimension;
    }

    public String getMove() {
        return move;
    }

    public void setMove(String move) {
        this.move = move;
    }

    public ArrayList<int[][]> getGoalStates() {
        return goalStates;
    }

    public void setGoalStates(ArrayList<int[][]> goalStates) {
        this.goalStates = goalStates;
    }
}



class ManhattanHeuristic implements Heuristic{

    @SuppressWarnings("Duplicates")
    @Override
    public double calculate(int[][] start_state, int[][] goal_state) {
        HashMap<Integer,Integer>map = new HashMap<>();

        int total = 0;
        if(allSame(goal_state[0])){//RowWise
           // System.out.println("Calculating Row Wise");
            for(int i=0;i<start_state.length;i++)
                map.put(goal_state[i][i],i);

            for(int i=0;i<start_state.length;i++){
                for (int j=0;j<start_state.length;j++){
                    int cur = start_state[i][j];
                    int posInGoal = map.get(cur);
                    int diff = Math.abs(i-posInGoal);
                    total+= Math.min(diff, start_state.length-diff);
                }
            }
        }
        else{//ColumnWise
            for(int i=0;i<start_state.length;i++)
                map.put(goal_state[i][i],i);

            for(int i=0;i<start_state.length;i++){
                for (int j=0;j<start_state.length;j++){
                    int cur = start_state[i][j];
                    int posInGoal = map.get(cur);
                    int diff = Math.abs(j-posInGoal);
                    total+= Math.min(diff, start_state.length-diff);
                }
            }
        }

        //return total;
        return 1.0*total/(1.0*start_state.length);
    }

    private boolean allSame(int[]state){
        for(int i=0;i<state.length-1;i++)
            if(state[i]!=state[i+1])
                return false;
        return true;
    }
}

class MismatchHeuristic implements Heuristic{

    @Override
    public double calculate(int[][] start_state, int[][] goal_state) {
        int count = 0;
        for (int i=0;i<start_state.length;i++){
            for(int j=0;j<start_state.length;j++){
                if(start_state[i][j]!=goal_state[i][j])count++;
            }
        }
        return count;
    }
}



public class Roll_1305043 {


    int[][] makeCopy(int[][]matrix)
    {
        int[][]ret = new int[matrix.length][];
        for(int i=0;i<matrix.length;i++){
            ret[i] = Arrays.copyOf(matrix[i],matrix[i].length);
        }
        return ret;
    }




    void main(){
        int[][] start_state = {
                {2,1,1,4},
                {4,2,1,4},
                {4,1,2,3},
                {3,3,3,2}
        };

        int[][] goal_state = {
                {1,1,1,1},
                {2,2,2,2},
                {3,3,3,3},
                {4,4,4,4}
        };

        int[][]col_gol = {
                {1, 2, 3, 4},
                {1, 2, 3, 4},
                {1, 2, 3, 4},
                {1, 2, 3, 4}
        };

        int[][]new_start = {
                {3,1,1,1},
                {2,2,4,2},
                {3,3,1,3},
                {2,4,4,4}
        };

        int[][]goal3 = {
                {1,1,1},
                {2,2,2},
                {3,3,3}
        };

        int[][]start3 = {
                {3,2,3},
                {1,1,3},
                {1,2,2}
        };

        int[][]main_input_state = null;

        BufferedReader bufferedReader = null;
        try {
            bufferedReader = new BufferedReader(new InputStreamReader(new DataInputStream(new FileInputStream("input.txt"))));
            String line = bufferedReader.readLine();
            line.trim();
            int len = Integer.parseInt(line);
            main_input_state = new int[len][len];
            for(int i=0;i<len;i++){
                line = bufferedReader.readLine();line.trim();
                String[]nums = line.split(" ");
                for(int j=0;j<len;j++){
                    main_input_state[i][j] = Integer.parseInt(nums[j]);
                }
            }

            line = bufferedReader.readLine();
            int x = Integer.parseInt(line);

            assert x == 0;


        } catch (IOException e) {
            e.printStackTrace();
        }


//      System.out.println(new ManhattanHeuristic().calculate(start_state,col_gol));
        //Cube cube1 = new Cube(this.makeCopy(new_start),this.makeCopy(goal_state));
        //Cube cube1 = new Cube(this.makeCopy(start_state),this.makeCopy(goal_state));
       // Cube cube1 = new Cube(this.makeCopy(start3),this.makeCopy(goal3));
        Cube cube1 =new Cube(this.makeCopy(main_input_state),this.makeCopy(goal_state));

        ArrayList<Cube>path = cube1.solve(new ManhattanHeuristic(),true);
        printResult(path, "Manhattan");

    }

    synchronized void printResult(ArrayList<Cube> path, String heur){

        System.out.println("Heuristic: "+heur+"\nTotal steps needed: "+path.size());

        if(path.size()==0){
            System.out.println("Input is one of the target forms!!");
            return;
        }

        Collections.reverse(path);

        for(Cube c:path){
            System.out.println(c.getParent().printCurrentState());
            System.out.println(c.printMoveOnParent()+"\n");
        }
        System.out.println(path.get(path.size()-1).printCurrentState());

    }



    void cubeCheck(Cube cube){

        System.out.println(cube.printCurrentState());
//
//        cube.moveLeft(0);
//        cube.moveRight(0);
//
//        cube.moveUp(0);
//        cube.moveUp(0);
//        cube.moveDown(1);
//        cube.moveDown(3);

//        ArrayList<Cube>neighbours = cube.generateMoves();
//
//        System.out.println("Total neighbours: "+neighbours.size());
//        for (Cube neighbour : neighbours) {
//
//            System.out.println((neighbour.printCurrentState()));
//
//        }

    }

    void compareH(Cube cube1)
    {
        Thread t1 = new Thread(() -> {
            ArrayList<Cube>path = cube1.solve(new ManhattanHeuristic());
            printResult(path,"Manhattan");
        });
        Thread t2 = new Thread(() -> {
            ArrayList<Cube>path2 = cube1.solve(new MismatchHeuristic());
            printResult(path2, "Mismatch");
        });
        t2.start();
        t1.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
