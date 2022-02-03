package graphusage;

/**
 * It represents record format for this specific implementation
 * @author Daniele Di Palma
 */
public class Record {
  private String firstPlace;
  private String secondPlace;
  private double distance;

  public Record(String firstPlace, String secondPlace, double distance){
    this.firstPlace = firstPlace;
    this.secondPlace = secondPlace;
    this.distance = distance;
  }

  public String getFirstCity(){
    return this.firstPlace;
  }

  public String getSecondCity(){
    return this.secondPlace;
  }

  public double getDistance(){
    return this.distance;
  }
}
