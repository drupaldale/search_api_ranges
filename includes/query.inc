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
  

}
