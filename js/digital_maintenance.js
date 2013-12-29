
jQuery(function() {
  jQuery('th.dm-year-next').click(function() {
    year = jQuery(this).prev().text();
    prev_year = year - 6;
    jQuery.ajax({
      type: "POST",
    dataType: 'json',
    data: {'oxy_nids' : oxy_nids},
    url: "/dm_costs_oxy/next/"+year,
    success: function (data) {
      jQuery.each( data, function( key, val ) {
        jQuery(key).after(val);
      });
      jQuery('.data-year-'+prev_year).remove();
      //re-calculate row sum
      _sm_tasks_row();
    }
    });
  });

  jQuery('th.dm-year-prev').click(function() {
    year = parseInt(jQuery(this).next().text());
    next_year = year + 6;
    jQuery.ajax({
      type: "POST",
    dataType: 'json',
    data: {'oxy_nids' : oxy_nids},
    url: "/dm_costs_oxy/prev/"+year,
    success: function (data) {
      jQuery.each( data, function( key, val ) {
        jQuery(key).before(val);
      });
    }
    });
    jQuery('.data-year-'+next_year).remove();
    //re-calculate row sum
    _sm_tasks_row();
  });


});

function _sm_tasks_row() {
  var total = 0;
  jQuery(".table tr.data-task").each(function() {
    var task_sum = 0;
    jQuery(this).find('td.data-year').each(function() {
      task_sum += parseInt(jQuery(this).text());
    });
    total += task_sum;
    jQuery(this).find('td.dm-sum-task').text(task_sum);
  });
  jQuery(".table td.dm-overalltotal").text(total);
}
