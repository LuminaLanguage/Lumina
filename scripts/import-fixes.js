const fs = require('fs');
const path = require('path');

const rootDir = path.resolve('src');

// Recursively collect all header files
function collectHeaders(dir, headers = {}) {
  const files = fs.readdirSync(dir);
  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);
    if (stat.isDirectory()) collectHeaders(fullPath, headers);
    else if (file.endsWith('.h')) headers[file] = fullPath;
  }
  return headers;
}

const headersMap = collectHeaders(rootDir);

function fixIncludes(dir) {
  const files = fs.readdirSync(dir);

  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);

    if (stat.isDirectory()) {
      fixIncludes(fullPath);
      continue;
    }

    if (!file.endsWith('.cpp') && !file.endsWith('.h')) continue;

    let content = fs.readFileSync(fullPath, 'utf8');
    let modified = false;

    content = content.replace(/#include ["<](.*?)[">]/g, (match, includeFile) => {
      // Ignore system headers with paths
      if (includeFile.includes('/') || includeFile.endsWith('.h') === false) return match;

      let newPath = null;

      // 1. Check same folder
      const sameFolder = path.join(path.dirname(fullPath), includeFile);
      if (fs.existsSync(sameFolder)) newPath = './' + includeFile;

      // 2. Else, check anywhere in headersMap
      else if (headersMap[includeFile]) {
        newPath = path.relative(path.dirname(fullPath), headersMap[includeFile]).replace(/\\/g, '/');
      }

      if (newPath && newPath !== includeFile) {
        modified = true;
        return `#include "${newPath}"`;
      }

      return match; // leave as-is
    });

    if (modified) fs.writeFileSync(fullPath, content, 'utf8');
  }
}

fixIncludes(rootDir);
console.log('Include paths fixed!');
