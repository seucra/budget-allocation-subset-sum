// frontend/src/react-window.d.ts

// Workaround for TypeScript error ts(2307) when importing submodules of react-window.
// It tells TypeScript that this module path exists and exports a default component.
declare module 'react-window/fixed-size-list' {
    import { FixedSizeList } from 'react-window';
    export default FixedSizeList;
}