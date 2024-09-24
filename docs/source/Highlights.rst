Highlights
==========

.. raw:: html

    <div class="slideshow-container">
        <div class="mySlides fade">
            <img src="/highlights_img/highlights-1.png"  
        style="width:100%">
            <div class="Harvesting of aerial humidity with natural hygroscopic salt excretions">Scientific Case 1</div>
        </div>

        <div class="mySlides fade">
            <img src="/highlights_img/highlights-2.png"
        style="width:100%">
            <div class="MOF-based device enables harvesting of atmospheric water from dry, desert air">Scientific Case 2</div>
        </div>
    
        <div class="mySlides fade">
            <img src="/highlights_img/highlights-3.png" 
        style="width:100%">
            <div class="SESAME shines light on improved hydrogen storage">Scientific Case 3</div>
        </div>
    </div>

    <br>

    <div style="text-align:center">
        <span class="dot"></span> 
        <span class="dot"></span> 
        <span class="dot"></span> 
    </div>

.. raw:: html

    <style>
    .slideshow-container {
      position: relative;
      max-width: 100%;
      margin: auto;
    }
    .mySlides {
      display: none;
    }
    .fade {
      -webkit-animation-name: fade;
      -webkit-animation-duration: 1.5s;
      animation-name: fade;
      animation-duration: 1.5s;
    }
    @keyframes fade {
      from {opacity: .4} 
      to {opacity: 1}
    }
    .text {
      color: #f2f2f2;
      font-size: 15px;
      position: absolute;
      bottom: 8px;
      width: 100%;
      text-align: center;
    }
    .dot {
      height: 15px;
      width: 15px;
      margin: 0 2px;
      background-color: #bbb;
      border-radius: 50%;
      display: inline-block;
      transition: background-color 0.6s ease;
    }
    .active {
      background-color: #717171;
    }
    </style>

    <script>
    var slideIndex = 0;
    showSlides();

    function showSlides() {
      var i;
      var slides = document.getElementsByClassName("mySlides");
      var dots = document.getElementsByClassName("dot");
      for (i = 0; i < slides.length; i++) {
        slides[i].style.display = "none";  
      }
      slideIndex++;
      if (slideIndex > slides.length) {slideIndex = 1}    
      for (i = 0; i < dots.length; i++) {
        dots[i].className = dots[i].className.replace(" active", "");
      }
      slides[slideIndex-1].style.display = "block";  
      dots[slideIndex-1].className += " active";
      setTimeout(showSlides, 5000); // Change image every 5 seconds
    }
    </script>
