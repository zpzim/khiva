// Copyright (c) 2019 Shapelets.io
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef KHIVA_CORE_MATRIX_H
#define KHIVA_CORE_MATRIX_H

#include <arrayfire.h>

namespace khiva {

namespace matrix {

/**
 * @brief Calculates the N best matches of several queries in several time series.
 *
 * The result has the following structure:
 *  - 1st dimension corresponds to the nth best match.
 *  - 2nd dimension corresponds to the number of queries.
 *  - 3rd dimension corresponds to the number of time series.
 *
 * For example, the distance in the position (1, 2, 3) corresponds to the second best distance of the third query in the
 * fourth time series. The index in the position (1, 2, 3) is the is the index of the subsequence which leads to the
 * second best distance of the third query in the fourth time series.
 *
 * @param q Array whose first dimension is the length of the query time series and the second dimension is the number of
 * queries.
 * @param t Array whose first dimension is the length of the time series and the second dimension is the number of time
 * series.
 * @param n Number of matches to return.
 * @param distances Resulting distances.
 * @param indexes Resulting indexes.
 */
void findBestNOccurrences(af::array q, af::array t, long n, af::array &distances, af::array &indexes);

/**
 * @brief Mueen's Algorithm for Similarity Search.
 *
 * The result has the following structure:
 *  - 1st dimension corresponds to the index of the subsequence in the time series.
 *  - 2nd dimension corresponds to the number of queries.
 *  - 3rd dimension corresponds to the number of time series.
 *
 * For example, the distance in the position (1, 2, 3) correspond to the distance of the third query to the fourth time
 * series for the second subsequence in the time series.
 *
 * [1] Chin-Chia Michael Yeh, Yan Zhu, Liudmila Ulanova, Nurjahan Begum, Yifei Ding, Hoang Anh Dau, Diego Furtado Silva,
 * Abdullah Mueen, Eamonn Keogh (2016). Matrix Profile I: All Pairs Similarity Joins for Time Series: A Unifying View
 * that Includes Motifs, Discords and Shapelets. IEEE ICDM 2016.
 *
 * @param q Array whose first dimension is the length of the query time series and the second dimension is the number of
 * queries.
 * @param t Array whose first dimension is the length of the time series and the second dimension is the number of time
 * series.
 * @param distances Resulting distances.
 */
void mass(af::array q, af::array t, af::array &distances);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 'ta' and 'tb' using a subsequence length of 'm'.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param ta Query time series.
 * @param tb Reference time series.
 * @param m Subsequence length.
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence from 'ta'
 * in 'tb'.
 * @param index The matrix profile index, which points to where the aforementioned minimum is located.
 */
void stomp(af::array ta, af::array tb, long m, af::array &profile, af::array &index);

/**
 * @brief STOMP algorithm to calculate the matrix profile between 't' and itself using a subsequence length of 'm'.
 * This method filters the trivial matches.
 *
 * [1] Yan Zhu, Zachary Zimmerman, Nader Shakibay Senobari, Chin-Chia Michael Yeh, Gareth Funning, Abdullah Mueen,
 * Philip Brisk and Eamonn Keogh (2016). Matrix Profile II: Exploiting a Novel Algorithm and GPUs to break the one
 * Hundred Million Barrier for Time Series Motifs and Joins. IEEE ICDM 2016.
 *
 * @param t Query and reference time series.
 * @param m Subsequence length.
 * @param profile The matrix profile, which reflects the distance to the closer element of the subsequence from 't' in a
 * different location of itself.
 * @param index The matrix profile index, which points to where the aforementioned minimum is located.
 */
void stomp(af::array t, long m, af::array &profile, af::array &index);

/**
 * @brief This function extracts the best N motifs from a previously calculated matrix profile.
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of motifs to extract.
 * @param motifs The distance of the best N motifs.
 * @param motifsIndices The indices of the best N motifs.
 * @param subsequenceIndices The indices of the query sequences that produced the minimum reported in the motifs
 * output array.
 * @param selfJoin Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 */
void findBestNMotifs(af::array profile, af::array index, long m, long n, af::array &motifs, af::array &motifsIndices,
                     af::array &subsequenceIndices, bool selfJoin = false);

/**
 * @brief This function extracts the best N discords from a previously calculated matrix profile.
 *
 * @param profile The matrix profile containing the minimum distance of each subsequence.
 * @param index The matrix profile index containing where each minimum occurs.
 * @param m Subsequence length value used to calculate the input matrix profile.
 * @param n Number of discords to extract.
 * @param discords The distance of the best N discords.
 * @param discordsIndices The indices of the best N discords.
 * @param subsequenceIndices The indices of the query sequences that produced the discords reported in the discords
 * output array.
 * @param selfJoin Indicates whether the input profile comes from a self join operation or not. It determines
 * whether the mirror similar region is included in the output or not.
 */
void findBestNDiscords(af::array profile, af::array index, long m, long n, af::array &discords,
                       af::array &discordsIndices, af::array &subsequenceIndices, bool selfJoin = false);

}  // namespace matrix
}  // namespace khiva

#endif
