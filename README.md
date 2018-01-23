# Deterministic Stateless Shuffle Algorithm

## Motivation
When playing board games I am often given a set of cards or tiles to shuffle. These cards must be kept face-down and ideally arranged in such a way that each card has an equal probability of ending up in any position. A standard riffle shuffle is typically not an option due to the unwieldy size or shape of the cards.
My general approach is to approximate a perfect riffle shuffle by unweaving the deck of cards into two piles, and mix in some arbitrary decisions such as creating a third pile or placing two cards in a row into the same pile. Arbitrary decisions are mentally taxing, however, so it would be desireable to be able to shuffle the cards in a deterministic way. Since the cards must remain face-down, the algorithm must also be stateless.

## Evaluation Metric
It's important to have a metric of comparison to evaluate shuffle algorithms against each other. Repeated applications of a deterministic shuffle algorithm will necessarily return the deck to its original state after a set number of iterations. My hypothesis is that the longer this cycle, the better the shuffle. A shuffle that steps through each permutation of the deck would be ideal according to this metric, but it would require state. On the other extreme, a shuffle that returns the deck as-is would be the worst possible shuffle, which is correct.

## Approach
There are three algorithms I've written for the purpose of evaluation:

### Standard Shuffle
This is the algorithm described earlier. The deck is simply delt out into two piles, and then the first pile is placed atop the second. It is the simplest reasonable deterministic stateless shuffle I am aware of.
#### Example
Deck: 0123456789ABCDEF
Pile1: ECA86420
Pile2: FDB97531
Result: ECA86420FDB97531
#### Performance
Repeats after 8 applications for a deck of size 16.

### Square-root Shuffle
This algorithm is the same as the standard shuffle, except the N cards are delt into sqrt(N) piles rather than just two. This means that the number of the cards in each pile will be approximately equal to the number of piles.
#### Example
Deck: 0123456789ABCDEF
Pile1: C840
Pile2: D951
Pile3: EA62
Pile4: FB73
Result: C840D951EA62FB73
#### Performance
Repeats after 4 applications for a deck of size 16.

### Triangle Shuffle
Similar to the standard shuffle, but starts with a single pile and adds a new pile with each iteration. The cards are added to the piles in reverse order, so the last card in each iteration ends up on the first pile.
#### Example
Deck: 0123456789ABCDEF
Pile1: E9520
Pile2: D841
Pile3: C73
Pile4: B6
Pile5: A
Pile6: F
Result: E9520D841C73B6AF
#### Performance
Repeats after 10 applications for a deck of size 16.

## Comparison
There are two cases worth considering as a basis for comparison:

### Baseline
A shuffle where the top card is placed on the bottom. This is obviously a bad shuffle.
#### Example
Deck: 0123456789ABCDEF
Result: 123456789ABCDEF0
#### Performance
Repeats after 16 applications for a deck of size 16.

### Ideal
A hypothetical perfect shuffle should iterate through every possible permutation of the cards.
#### Example
Deck: 0123456789ABCDEF
Result: 0123456789ABCDFE
#### Performance
Repeats after 20922789888000 (16P16) applications for a deck of size 16.

## Conclusion
Despite producing reasonably random looking results after a single application, repeated application of each of these algorithms performed significantly worse than even the baseline case. In fact, for the given constraints and evaluation metric the optimal algorithm appears to be the following.

### Coprime Partition Shuffle
Divide the deck into partitions of sizes that are coprime. On each iteration perform the baseline shuffle on each partition.
#### Example
Deck: 0123456789ABCDEF
Pile1: 01
Pile2: 234
Pile3: 56789
Pile4: ABCDEF
Result: 1034267895BCDEFA
#### Performance
Repeats after 30 (2×3×5) applications for a deck of size 16.

## Future Work
Due to the disappointing conclusion with the given constraints it may be possible to produce a more practical deterministic shuffling algorithm by introducing a small amount of state. Some potential ideas include:
* One bit of state used to alternate between two different mappings.
* A counter to increment the position at which a mapping begins.
