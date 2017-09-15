import junit.framework.TestCase;
import java.util.ArrayList;

public class TestHand extends TestCase {
  public void testConstructor()
  {
    ArrayList<Card> cards = new ArrayList<Card>();
    
    for (int i = 2; i < 15; i++) {
      cards.add(new Card(i, 'C'));
    }

    Hand test_hand = new Hand(cards);
    ArrayList<Card> test_cards = test_hand.getHand();

    for (int i = 0; i < 13; i++) {
      assertEquals(test_cards.get(i).getRank(), cards.get(i).getRank());
    }
  }

  public void testAddCards()
  {
    Hand test_hand = new Hand();

    test_hand.addCard(new Card("8C"));
    test_hand.addCard(new Card("2H"));
    test_hand.addCard(new Card("KS"));
    test_hand.addCard("10H");
    test_hand.addCard("AH");

    ArrayList<Card> test_cards = test_hand.getHand();

    assertEquals(test_cards.get(0).getCard(), "8C");
    assertEquals(test_cards.get(1).getCard(), "2H");
    assertEquals(test_cards.get(2).getCard(), "KS");
    assertEquals(test_cards.get(3).getCard(), "10H");
    assertEquals(test_cards.get(4).getCard(), "AH");
  }

  public void testDiscard()
  {
    ArrayList<Card> cards = new ArrayList<Card>();
    
    for (int i = 2; i < 6; i++) {
      cards.add(new Card(i, 'C'));
    }
    ArrayList<Card> test_cards;
    Hand test_hand = new Hand(cards);
    
    test_hand.discard("2C");
    test_cards = test_hand.getHand();
    assertEquals(test_cards.get(0).getCard(), "3C");

    test_hand.discard(cards.get(0));
    test_cards = test_hand.getHand();
    assertEquals(test_cards.get(0).getCard(), "4C");
  }

  public void testEvaluations()
  {
    Hand test_hand = new Hand();
    test_hand.addCard(new Card("8C"));
    test_hand.addCard(new Card("2H"));
    test_hand.addCard(new Card("KS"));
    test_hand.addCard(new Card("10H"));
    test_hand.addCard(new Card("AH"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.HighCard.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("8C"));
    test_hand.addCard(new Card("2H"));
    test_hand.addCard(new Card("KS"));
    test_hand.addCard(new Card("2C"));
    test_hand.addCard(new Card("AH"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.TwoKind.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("8C"));
    test_hand.addCard(new Card("8H"));
    test_hand.addCard(new Card("KS"));
    test_hand.addCard(new Card("2C"));
    test_hand.addCard(new Card("KH"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.TwoPair.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("AC"));
    test_hand.addCard(new Card("2H"));
    test_hand.addCard(new Card("AS"));
    test_hand.addCard(new Card("JC"));
    test_hand.addCard(new Card("AH"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.ThreeKind.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("AC"));
    test_hand.addCard(new Card("3H"));
    test_hand.addCard(new Card("5S"));
    test_hand.addCard(new Card("4C"));
    test_hand.addCard(new Card("2H"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.Straight.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("KC"));
    test_hand.addCard(new Card("10H"));
    test_hand.addCard(new Card("JS"));
    test_hand.addCard(new Card("QC"));
    test_hand.addCard(new Card("AH"));

    test_hand.evaluate();
    // TODO: fix this
    assertEquals(Hand.Evaluation.Straight.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("9C"));
    test_hand.addCard(new Card("8H"));
    test_hand.addCard(new Card("7S"));
    test_hand.addCard(new Card("10C"));
    test_hand.addCard(new Card("6H"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.Straight.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("9C"));
    test_hand.addCard(new Card("3C"));
    test_hand.addCard(new Card("AC"));
    test_hand.addCard(new Card("JC"));
    test_hand.addCard(new Card("6C"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.Flush.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("9C"));
    test_hand.addCard(new Card("3C"));
    test_hand.addCard(new Card("3H"));
    test_hand.addCard(new Card("9D"));
    test_hand.addCard(new Card("3S"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.FullHouse.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("JC"));
    test_hand.addCard(new Card("JH"));
    test_hand.addCard(new Card("3H"));
    test_hand.addCard(new Card("JD"));
    test_hand.addCard(new Card("JS"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.FourKind.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("JC"));
    test_hand.addCard(new Card("QC"));
    test_hand.addCard(new Card("10C"));
    test_hand.addCard(new Card("AC"));
    test_hand.addCard(new Card("KC"));

    test_hand.evaluate();
    // TODO: fix this
    assertEquals(Hand.Evaluation.StraightFlush.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("AS"));
    test_hand.addCard(new Card("4S"));
    test_hand.addCard(new Card("2S"));
    test_hand.addCard(new Card("3S"));
    test_hand.addCard(new Card("5S"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.StraightFlush.value(), test_hand.getEvaluation().value());

    test_hand = new Hand();
    test_hand.addCard(new Card("5D"));
    test_hand.addCard(new Card("7D"));
    test_hand.addCard(new Card("6D"));
    test_hand.addCard(new Card("9D"));
    test_hand.addCard(new Card("8D"));

    test_hand.evaluate();
    assertEquals(Hand.Evaluation.StraightFlush.value(), test_hand.getEvaluation().value());
  }
}
