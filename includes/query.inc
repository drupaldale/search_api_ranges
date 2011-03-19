<?php

/**
 * Standard implementation of SearchApiQueryInterface.
 */
class SearchApiRangesQuery extends SearchApiQuery {

  /**
   * The index.
   *
   * @var SearchApiIndex
   */
  protected $index;

  /**
   * The search keys. If NULL, this will be a filter-only search.
   *
   * @var mixed
   */
  protected $keys;

  /**
   * The unprocessed search keys, as passed to the keys() method.
   *
   * @var mixed
   */
  protected $orig_keys;

  /**
   * The fields that will be searched for the keys.
   *
   * @var array
   */
  protected $fields;

  /**
   * The search filter associated with this query.
   *
   * @var SearchApiQueryFilterInterface
   */
  protected $filter;

  /**
   * The sort associated with this query.
   *
   * @var array
   */
  protected $sort;

  /**
   * Search options configuring this query.
   *
   * @var array
   */
  protected $options;

  /**
   * Count for providing a unique ID.
   */
  protected static $count = 0;
  
  /**
   * Executes this search query in a clean manner, for self-contained searches.
   *
   * @return array
   *   An associative array containing the search results. The following keys
   *   are standardized:
   *   - 'result count': The overall number of results for this query, without
   *     range restrictions. Might be approximated, for large numbers.
   *   - results: An array of results, ordered as specified. The array keys are
   *     the items' IDs, values are arrays containing the following keys:
   *     - id: The item's ID.
   *     - score: A float measuring how well the item fits the search.
   *     - entity (optional): If set, the fully loaded entity. This field should
   *       always be used by modules using search results, to avoid duplicate
   *       entity loads.
   *     - excerpt (optional): If set, an HTML text containing highlighted
   *       portions of the fulltext that match the query.
   *   - warnings: A numeric array of translated warning messages that may be
   *     displayed to the user.
   *   - ignored: A numeric array of search keys that were ignored for this
   *     search (e.g., because of being too short or stop words).
   *   - performance: An associative array with the time taken (as floats, in
   *     seconds) for specific parts of the search execution:
   *     - complete: The complete runtime of the query.
   *     - hooks: Hook invocations and other server-independent processing.
   *     - preprocessing: Preprocessing of the service class.
   *     - execution: The actual query to the search server, in whatever form.
   *     - postprocessing: Preparing the results for returning.
   *   Additional metadata may be returned in other keys. Only 'result count'
   *   and 'results' always have to be set, all other entries are optional.
   */
  public final function executeClean() {
    $start = microtime(TRUE);

    // Add filter for languages.
    if (isset($this->options['languages'])) {
      $this->addLanguages($this->options['languages']);
    }

    // Add fulltext fields, unless set
    if ($this->fields === NULL) {
      $this->fields = $this->index->getFulltextFields();
    }

    // Call pre-execute hook.
    $this->preExecute();

    // Preprocess query.
    $this->index->preprocessSearchQuery($this);

    $pre_search = microtime(TRUE);

    // Execute query.
    $response = $this->index->server()->search($this);

    $post_search = microtime(TRUE);

    // Call post-execute hook.
    $this->postExecute($response);

    // Postprocess results.
    $this->index->postprocessSearchResults($response, $this);

    $end = microtime(TRUE);
    $response['performance']['complete'] = $end - $start;
    $response['performance']['hooks'] = $response['performance']['complete'] - ($post_search - $pre_search);

    return $response;
  } 
}