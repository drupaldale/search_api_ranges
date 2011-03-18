(function($){
  Drupal.behaviors.search_api_ranges = {
    attach: function(context, settings){
      
      var submitTimeout = '';
    
      $('div.search-api-ranges-widget').each(function(){
        var widget = $(this);
        var slider = widget.find('div.range-slider');
        var rangeMin = widget.find('input[name=range-min]');
        var rangeMax = widget.find('input[name=range-max]');
        var rangeFrom = widget.find('input[name=range-from]');
        var rangeTo = widget.find('input[name=range-to]');
        
        slider.slider({
          range: true,
          min: parseInt(rangeMin.val()),
          max: parseInt(rangeMax.val()),
          values: [parseInt(rangeFrom.val()), parseInt(rangeTo.val())],
          slide: function(event, ui){
            clearTimeout(submitTimeout);
            var values = slider.slider("option", "values");
            widget.find('input[name=range-from]').val(values[0]);
            widget.find('input[name=range-to]').val(values[1]);
            delaySubmit(widget);
          }
        });
        
        rangeFrom.bind('keyup', function(){
          clearTimeout(submitTimeout);
          var value = parseInt(rangeFrom.val());
          if (value > parseInt(rangeTo.val())) {
            value = parseInt(rangeTo.val());
          }
          slider.slider("option", "values", [value, parseInt(rangeTo.val())]);
          delaySubmit(widget);
        });
        
        rangeTo.bind('keyup', function(){
          clearTimeout(submitTimeout);
          var value = parseInt(rangeTo.val());
          if (value < parseInt(rangeFrom.val())) {
            value = parseInt(rangeFrom.val());
          }
          slider.slider("option", "values", [parseInt(rangeFrom.val()), value]);
          delaySubmit(widget);
        });
      });
      
      function delaySubmit(widget){
        submitTimeout = setTimeout(function(){
          widget.find('form').submit();
        }, 1500);
      };
    }
  };
})(jQuery);
