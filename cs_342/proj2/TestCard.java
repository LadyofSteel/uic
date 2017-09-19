import junit.framework.TestCase;

public class TestCard extends TestCase {
  public void testConstructor()
  {
    Card test_card = new Card(5, 'H');
    assertEquals(5, test_card.getRank());
    assertEquals('H', test_card.getSuit());

    test_card = new Card("10H");
    assertEquals(10, test_card.getRank());
    assertEquals('H', test_card.getSuit());

    test_card = new Card("QC");
    assertEquals(12, test_card.getRank());
    assertEquals('C', test_card.getSuit());

    test_card = new Card("AS");
    assertEquals(14, test_card.getRank());
    assertEquals('S', test_card.getSuit());
  }

  public void testGetCard()
  {
    int rank = 5;
    char suit = 'H';

    Card test_card = new Card(rank, suit);

    assertEquals(test_card.getCard(), "5H");

    test_card.setRank(10);
    assertEquals(test_card.getCard(), "10H");

    test_card.setRank(12);
    assertEquals(test_card.getCard(), "QH");

    test_card.setRank(14);
    assertEquals(test_card.getCard(), "AH");
  }
}
