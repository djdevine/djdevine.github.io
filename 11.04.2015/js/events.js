$("a").click(function(e){
    var targetOffset= $("#links").offset().top;
    $('html, body').animate({scrollTop: targetOffset}, 1500);
    e.preventDefault();    
});