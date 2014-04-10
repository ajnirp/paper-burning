## About

Simulation of paper burning in two dimensions. Deformation of the paper due to burning hasn't been modeled.

## Notes on Patchiness vs Spread Regularity

Lower the threshold, the likelier it is that propagation happens. If probability of propagation is 1, expansion happens in a diamond fashion, with no patches at all.

Patches are almost never seen in the case of online computation of spread probability. In the case of offline texmap storage, we have two choices: either store the out-of-cell transition probabilities, or store just one into-cell transition probability. The second method requires 1/K times the amount of storage space as the first method, but if a cell has a low into-cell probability, it is very likely doomed to end up as an unburnt patch. The first method also has patchiness, probably due to the fact that the out-of-cell transitions do not change (after all, we are only reading a precomputed texture). Consider a cell that just started burning. Since the four out-of-cell probabilities in the case of online computation are computed anew in each iteration, the out-of-cell probability that will burn a specific unburnt neighbour cell has 10 chances to be a 'good' value. By contrast, in offline computation, it is pretty much set in stone what the out-of-cell probabilities are going to be - they do not change over 10 iterations.