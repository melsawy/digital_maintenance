
jQuery(function() {
  
  jQuery('th.dm-year-next div.dm-loading').hide();
  jQuery('th.dm-year-prev div.dm-loading').hide();
  
  jQuery('th.dm-year-next div.dm-apply').click(function() {
    jQuery('th.dm-year-next div.dm-loading').show();
    jQuery('th.dm-year-next div.dm-apply').hide();
    year = jQuery(this).parent().prev().text();
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
    },
    complete: function() {
      jQuery('th.dm-year-next div.dm-loading').hide();
      jQuery('th.dm-year-next div.dm-apply').show();
      pdf_year = prev_year + 1;
      _update_pdf_link(pdf_year);
    }
    });
  });

  jQuery('th.dm-year-prev').click(function() {
    jQuery('th.dm-year-prev div.dm-loading').show();
    jQuery('th.dm-year-prev div.dm-apply').hide();
    year = parseInt(jQuery(this).next().text());
    next_year = year + 6;
    jQuery.ajax({
      type: "POST",
    dataType: 'json',
    data: {'oxy_nids' : oxy_nids},
    url: "/dm_costs_oxy/prev/"+year,
    success: function (data) {
      jQuery('.data-year-'+next_year).remove();
      jQuery.each( data, function( key, val ) {
        jQuery(key).before(val);
      });
      //re-calculate row sum
      _sm_tasks_row();
    },
    complete: function() {
      jQuery('th.dm-year-prev div.dm-loading').hide();
      jQuery('th.dm-year-prev div.dm-apply').show();
      pdf_year = year - 1;
      _update_pdf_link(pdf_year);
    }

    });
  });

  //Select tasklist view
  jQuery('.dm-taskview-list .form-select').change(function() {
    url = Drupal.settings.basePath + jQuery(this).val();
    jQuery(location).attr('href',url);
  });

  //Change task status
  jQuery('.dm-task-progress .form-select').change(function() {
    var task_status = jQuery(this).val();
    if (task_status == 3) {
      jQuery('.dm-task-comment').removeClass('hidden');
    }
    else {
      jQuery('.dm-task-comment').addClass('hidden');
    }
    /*
    var task_nid = jQuery('.dm-task-progress').attr('data-nid');
    jQuery.ajax({
      type: "POST",
      dataType: 'json',
      data: {'nid' : task_nid, 'status' : task_status},
      url: "/boligweb/dm_task/update_status",
      success: function (data) {
        alert('Updated task status.');
      },
    });
    */
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

function _update_pdf_link(year) {
  jQuery('.dm-generate-pdf a').attr('href', '/dm_pdf/budget/'+year);
}
