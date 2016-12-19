package gaming;

/**
 * Created by numan947 on 12/18/16.
 **/
public class Player {
    private String username;
    private int rating;
    private int matchCount;
    private int winCount;
    private int bestScore;
    private int totalXP;


    public Player(String username, int rating, int matchCount, int winCount, int bestScore, int totalXP) {
        this.username = username;
        this.rating = rating;
        this.matchCount = matchCount;
        this.winCount = winCount;
        this.bestScore = bestScore;
        this.totalXP = totalXP;
    }


    public String getUsername() {
        return username;
    }

    public int getRating() {
        return rating;
    }

    public int getMatchCount() {
        return matchCount;
    }

    public int getWinCount() {
        return winCount;
    }

    public int getBestScore() {
        return bestScore;
    }

    public int getTotalXP() {
        return totalXP;
    }
}
