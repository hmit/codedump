/* package whatever; // don't place package name! */
import java.util.*;
import java.lang.*;
import java.io.*;
import java.nio.*;

/* Name of the class has to be "Main" only if the class is public. */
public class Bowling
{
  private static boolean Debug = false;
	public static void main (String[] args) throws java.lang.Exception
	{
		// your code goes here
    testBowlingScores();
    String mySheet = "2,3,x,,5,/,4,5,x,,x,,6,/,7,2,8,1,x,x,x";
		System.out.println("totScore: " + getBowlingScore(mySheet));
	}

  public static void testBowlingScores() {
    String mySheet = "2,3,x,,5,/,4,5,x,,x,,6,/,7,2,8,1,x,x,x";
    assert(getBowlingScore(mySheet) == 159);
    mySheet = "x,,x,,x,,x,,x,,x,,x,,x,,x,,x,x,x";
    assert(getBowlingScore(mySheet) == 300);

  }

  public static int getBowlingScore(String scoreSheet) {
    String[] scores = new String(scoreSheet).split(",");
		int totScore = 0, prev = 0, bonus = 0;
    int[] bonusArr = new int[scores.length];
    int counter = 0;
		for (int i = 0; i < scores.length; i++) {
      if (scores[i].length() == 0) {
        continue;
      }
      bonusArr[counter] = 0;
			char scChr = scores[i].trim().charAt(0);
			if (scChr == '\0') {
				continue;
			}
			int score = 0, nb = 0;
			if (scChr >= '1' && scChr <= '9') {
				score = scChr - '0';
				prev = score;
			}
			if (scChr == '/') {
				score = 10 - prev;
        bonusArr[counter] = 1;
			}
			if (scChr == 'x') {
				score = 10;
        bonusArr[counter] = 2;
			}

      boolean p1Bonus = (counter - 1 >= 0 && i < 19 && bonusArr[counter - 1] > 0);
      boolean p2Bonus = (counter - 2 >= 0 && i < 20 && bonusArr[counter - 2] > 1);
			totScore += score + ((p1Bonus) ? score : 0) + ((p2Bonus) ? score : 0);
      if (Debug) {
        System.out.println("char " + i + " " + scores[i] + " " + score + " " + totScore + " " + bonusArr[counter]);
      }
      counter++;
		}
    return totScore;
  }
}
