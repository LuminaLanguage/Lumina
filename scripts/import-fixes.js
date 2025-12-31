const fs = require('fs');
const path = require('path');

const rootDir = path.resolve('src');

function fixIncludes(dir) {
  const files = fs.readdirSync(dir);

  for (const file of files) {
    const fullPath = path.join(dir, file);
    const stat = fs.statSync(fullPath);

    if (stat.isDirectory()) {
      fixIncludes(fullPath);
    } else if (file.endsWith('.cpp') || file.endsWith('.h')) {
      let content = fs.readFileSync(fullPath, 'utf8');

      // Fix local includes
      content = content.replace(/#include "(.*?)"/g, (match, includeFile) => {
        const includePath = path.join(dir, includeFile);
        if (fs.existsSync(includePath)) {
          const relativePath = path.relative(path.dirname(fullPath), includePath);
          return `#include "${relativePath.replace(/\\/g, '/')}"`;
        }
        return match;
      });

      fs.writeFileSync(fullPath, content, 'utf8');
    }
  }
}

fixIncludes(rootDir);
console.log('Include paths fixed!');
