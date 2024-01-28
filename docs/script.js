document.addEventListener("DOMContentLoaded", function () {
    let currentImageIndex = 0;
    const images = ["Fusion.png", "Rubik's-solver.png", "Rubik's-solver.jpeg"]; // Add more image URLs as needed
    const slideshowInterval = 5000; // 5 seconds

    function showNextImage() {
        currentImageIndex = (currentImageIndex + 1) % images.length;
        const imageSrc = images[currentImageIndex];
        document.querySelector(".slideshow-img").src = imageSrc;
    }

    const slideshowTimer = setInterval(showNextImage, slideshowInterval);

    document.getElementById("image").addEventListener("click", function () {
        clearInterval(slideshowTimer); // Stop the slideshow when clicked
        // Add any additional behavior you want when the image is clicked
    });
});
