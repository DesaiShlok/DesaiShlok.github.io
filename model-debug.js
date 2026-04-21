const viewer = document.querySelector('model-viewer');
const zoomValue = document.querySelector('[data-zoom-value]');
const orbitValue = document.querySelector('[data-orbit-value]');

if (viewer && zoomValue && orbitValue) {
    const updateReadout = () => {
        const orbit = viewer.getCameraOrbit();
        const zoom = orbit.radius.toString();
        const orbitString = `${orbit.theta.toString()} ${orbit.phi.toString()} ${zoom}`;

        zoomValue.textContent = zoom;
        orbitValue.textContent = orbitString;
    };

    viewer.addEventListener('load', updateReadout);
    viewer.addEventListener('camera-change', updateReadout);
    updateReadout();
}