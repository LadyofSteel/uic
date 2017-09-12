import junit.framework.TestCase;
import java.util.Vector;

public class TestCardPile extends TestCase {
  public void testCards()
  {
    CardPile test_pile = new CardPile();
    Vector<Card> cards1 = new Vector<Card>();

    for (int i = 2; i < 15; i++)
      cards1.add(new Card(i, 'S'));

    test_pile.setCards(cards1);
    Vector<Card> cards2 = test_pile.getCards();

    assertTrue(cards1.equals(cards2));
  }

  public void testAddCard()
  {
    CardPile test_pile = new CardPile();

    for (int i = 2; i < 15; i++)
      test_pile.addCard(new Card(i, 'H'));

    Vector<Card> cards = test_pile.getCards();

    for (int i = 0; i < 13; i++) {
      int rank = cards.get(i).getRank();
      char suit = cards.get(i).getSuit();

      assertEquals(rank, i+2);
      assertEquals(suit, 'H');
    }
  }

  public void testDrawCard()
  {
    CardPile test_pile = new CardPile();

    for (int i = 2; i < 15; i++)
      test_pile.addCard(new Card(i, 'H'));

    assertEquals(test_pile.getNumberOfCards(), 13);

    Card card = test_pile.drawCard();

    assertEquals(card.getRank(), 14);
    assertEquals(test_pile.getNumberOfCards(), 12);

    card = test_pile.drawCard();
    assertEquals(card.getRank(), 13);
    assertEquals(test_pile.getNumberOfCards(), 11);
  }

  public void testNumCards()
  {
    CardPile test_pile = new CardPile();

    assertEquals(test_pile.getNumberOfCards(), 0);

    for (int i = 2; i < 15; i++)
      test_pile.addCard(new Card(i, 'H'));

    assertEquals(test_pile.getNumberOfCards(), 13);

    test_pile.addCard(new Card(3, 'S'));
    test_pile.addCard(new Card(8, 'D'));

    assertEquals(test_pile.getNumberOfCards(), 15);
  }

  public void testShuffle()
  {
    // How the hell do you test this?!?
  }
}
