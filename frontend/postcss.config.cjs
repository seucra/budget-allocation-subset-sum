// frontend/postcss.config.cjs
// This strict CJS syntax guarantees module resolution via require()
module.exports = {
  plugins: [
    require('tailwindcss'),
    require('autoprefixer'),
  ],
}